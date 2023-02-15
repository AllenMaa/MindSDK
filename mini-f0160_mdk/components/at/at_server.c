/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "at_server.h"

/*
 * Macros.
 */


/*
 * Declerations.
 */

/* at command parse. */
void at_parse(at_server_t * server);
/* get the at command name from at receive command buffer.*/
static bool at_cmd_get_name(char * cmd_buffer, char * cmd_name);
/* find the at command name from at command list. */
static at_cmd_t * at_find_cmd(at_server_t * server, char * cmd);
/* process the at command. */
static bool at_cmd_process(at_server_t * server, at_cmd_t * cmd, char * cmd_args);
/* check the ar command parameter format. */
static bool at_check_args(char * args, char * args_format);

/*
 * Variables.
 */

/*
 * Functions.
 */

void at_server_init(at_server_t * server,at_adapter_t * adapter)
{
    adapter->init();
    server->adapter = adapter;
    server->remaining = adapter->buf_size;
    memcpy(server->end_mark, AT_CMD_END_MARK_DEFAULT, sizeof(AT_CMD_END_MARK_DEFAULT));
}

void at_server_set_cmd_list(at_server_t * server, at_cmd_t * cmd_list[], uint32_t cmd_num)
{
    server->cmd_list = cmd_list;
    server->cmd_num = cmd_num;
}

void at_server_write(at_server_t * server, char * buf, uint32_t len)
{
    server->adapter->write(buf, len);
}

uint32_t at_server_read(at_server_t * server, char * buf, uint32_t len)
{
    return server->adapter->read(buf, len);
}

void at_server_task(at_server_t * server)
{
    char * matchstr=NULL; /* Represents the string left after being returned using the strstr function. */
    char * buf = &(server->adapter->buf[server->adapter->buf_size - server->remaining]);
    uint32_t len = at_server_read(server, buf, server->remaining);

    if (0u != len)
    {
        server->remaining -= len;
        while(1)   /* wait for all recipients in the received data to be compared. */
        {
            matchstr = strstr(server->adapter->buf, server->end_mark);
            if (NULL != matchstr)
            {
                at_parse(server);
                /* not copy the last matching terminator. */
                memcpy(server->adapter->buf, matchstr+strlen(server->end_mark), strlen(server->adapter->buf));
                server->remaining = server->adapter->buf_size - strlen(matchstr);
            }
            else
            {
                break;
            }
        }
    }
}

/*parse the receive datas.*/
void at_parse(at_server_t * server)
{
    char cur_cmd_name[AT_CMD_NAME_LEN] = { 0 };
    at_cmd_t * cur_cmd = NULL;
    char * cur_cmd_args = NULL;
    char * buf = server->adapter->buf;

    if (at_cmd_get_name(buf, cur_cmd_name) == false)
    {
        AT_LOG("ERROR CMD MATCH FAILED!\r\n");

        return;
    }

    cur_cmd = at_find_cmd(server, cur_cmd_name);
    if (cur_cmd == false)
    {
        AT_LOG("ERROR CMD MATCH FAILED!\r\n");

        return;
    }

    cur_cmd_args = buf + strlen(cur_cmd_name);
    if (at_cmd_process(server, cur_cmd, cur_cmd_args) == false)
    {
        AT_LOG("ERROR PARSE ARGS FAILED!\r\n");

        return;
    }
}

/* get at command name from at server receive buffer. */
static bool at_cmd_get_name(char * cmd_buffer, char * cmd_name)
{
    uint32_t cmd_name_len = 0u;

    for (uint32_t i = 0; i < strlen(cmd_buffer) + 1; i++)
    {
        if ( (*(cmd_buffer + i) == AT_CMD_QUESTION_MARK) || (*(cmd_buffer + i) == AT_CMD_EQUAL_MARK)
                || (*(cmd_buffer + i) == AT_CMD_CR)
                || ( (*(cmd_buffer + i) >= AT_CMD_CHAR_0) && (*(cmd_buffer + i) <= AT_CMD_CHAR_9) ) )
        {
            cmd_name_len = i;
            memcpy(cmd_name, cmd_buffer, cmd_name_len);
            *(cmd_name + cmd_name_len) = '\0';

            return true;
        }
    }
    return false;
}

/* find if the current at command name is in the at command list. */
static at_cmd_t * at_find_cmd(at_server_t * server, char * cmd)
{
    for (uint32_t i = 0; i < server->cmd_num; i++)
    {
        if (!strcasecmp(cmd,server->cmd_list[i]->name))
        {
            return server->cmd_list[i];
        }
    }

    return false;
}

/* parse command parameters and execute corresponding command functions. */
static bool at_cmd_process(at_server_t * server, at_cmd_t * cmd, char * cmd_args)
{
    at_result_t result = AT_RESULT_OK;

    if ( (cmd_args[0] == AT_CMD_EQUAL_MARK) && (cmd_args[1] == AT_CMD_QUESTION_MARK) && (cmd_args[2] == AT_CMD_CR) )
    {
        if (cmd->test == NULL)
        {
            AT_LOG("ERROR CHECK ARGS FORMAT FAILED!\r\n");

            return false;
        }

        result = cmd->test(server->adapter->write);
    }

    else if ( (cmd_args[0] == AT_CMD_QUESTION_MARK) && (cmd_args[1] == AT_CMD_CR) )
    {
        if (cmd->query == NULL)
        {
            AT_LOG("ERROR CHECK ARGS FORMAT FAILED!\r\n");

            return false;
        }
        result = cmd->query(server->adapter->write);
    }

    else if ( (cmd_args[0] == AT_CMD_EQUAL_MARK)
            || ( (cmd_args[0] >= AT_CMD_CHAR_0) && (cmd_args[0] <= AT_CMD_CHAR_9) && (cmd_args[1] == AT_CMD_CR) ) )
    {
        if (cmd->setup == NULL)
        {
            AT_LOG("ERROR CHECK ARGS FORMAT FAILED!\r\n");

            return false;
        }

        if(at_check_args(cmd_args, cmd->args_expr) == false)
        {
            AT_LOG("ERROR CHECK ARGS FORMAT FAILED!\r\n");;

           return false;
        }

        result = cmd->setup(server->adapter->write, cmd_args);
    }

    else if (cmd_args[0] == AT_CMD_CR)
    {
        if (cmd->exec == NULL)
        {

            return false;
        }

        result = cmd->exec(server->adapter->write);
    }

    else
    {
        return result;
    }

    return true;
}

/* check the ar command parameter format. */
static bool at_check_args(char * args, char * args_format)
{
    uint32_t left_sq_bracket_num = 0, right_sq_bracket_num = 0;
    uint32_t left_angle_bracket_num = 0, right_angle_bracket_num = 0;
    uint32_t comma_mark_num = 0;

    for (uint32_t i = 0; i < strlen(args_format); i++)
    {
        switch (args_format[i])
        {
        case AT_CMD_L_SQ_BRACKET:
            left_sq_bracket_num++;
            break;

        case AT_CMD_R_SQ_BRACKET:
            right_sq_bracket_num++;
            break;

        case AT_CMD_L_ANGLE_BRACKET:
            left_angle_bracket_num++;
            break;

        case AT_CMD_R_ANGLE_BRACKET:
            right_angle_bracket_num++;
            break;

        default:
            break;
        }
    }

    if ( (left_sq_bracket_num != right_sq_bracket_num) || (left_angle_bracket_num != right_angle_bracket_num)
            || (left_sq_bracket_num > left_angle_bracket_num) )
    {
        return -1;
    }

    for (uint32_t i = 0; i < strlen(args); i++)
    {
        if (args[i] == AT_CMD_COMMA_MARK)
        {
            comma_mark_num++;
        }
    }

    if ( (comma_mark_num + 1 < left_angle_bracket_num - left_sq_bracket_num)
            || (comma_mark_num + 1 > left_angle_bracket_num) )
    {
        return false;
    }

    return true;
}

/* parse the number of arguments to the at request instruction. */
int at_req_parse_args(const char * req_args, const char * req_expr, ...)
{
    va_list args;
    int req_args_num = 0;

    va_start(args, req_expr);
    req_args_num = vsscanf(req_args, req_expr, args);
    va_end(args);

    return req_args_num;
}

/* EOF. */
