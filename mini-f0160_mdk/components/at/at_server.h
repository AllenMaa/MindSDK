/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __AT_SERVER_H__
#define __AT_SERVER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/*!
 * @addtogroup AT
 * @{
 */

/*!
 * @brief AT component version number.
 */
#define AT_COMPONENT_VERSION 0u

/* AT LOG. */
/* when using AT_LOG, the user is required to implement printf function. */
#ifdef ENABLE_AT_LOG
#define AT_LOG(...)  printf("[AT]:");printf(__VA_ARGS__);
#else
#define AT_LOG(...)
#endif

/*!
 * @addtogroup AT_CMD_END_MARK
 * define at command end mark.
 * @{
 */

#define AT_CMD_END_MARK_DEFAULT        "\r\n" /* the end mark of at command. */
#define AT_END_MARK_LEN                4u     /* the length of at command end mark. */
#define AT_CMD_NAME_LEN                16u    /* the length of at command name. */

/*!
 * @}
 */

/*!
 * @addtogroup AT_CMD_PARAM_FORMAT
 * define the parameter format for at command.
 * @{
 */

#define AT_CMD_CHAR_0                  '0'
#define AT_CMD_CHAR_9                  '9'
#define AT_CMD_QUESTION_MARK           '?'
#define AT_CMD_EQUAL_MARK              '='
#define AT_CMD_L_SQ_BRACKET            '['
#define AT_CMD_R_SQ_BRACKET            ']'
#define AT_CMD_L_ANGLE_BRACKET         '<'
#define AT_CMD_R_ANGLE_BRACKET         '>'
#define AT_CMD_COMMA_MARK              ','
#define AT_CMD_SEMICOLON               ';'
#define AT_CMD_CR                      '\r'
#define AT_CMD_LF                      '\n'

/*!
 * @}
 */


/*!
 * @brief at result type.
 *
 * at command parsing result.
 */
typedef enum
{
    AT_RESULT_OK = 0,                 /* at command parsing result is no error */
    AT_RESULT_FAILE = 1,              /* at command parsing result have a generic error */
    AT_RESULT_NULL = 2,               /* at command parsing result not need return */
    AT_RESULT_CMD_ERR = 3,            /* at command format error or No way to execute */
    AT_RESULT_CHECK_FAILE = 4,        /* at command expression format is error */
    AT_RESULT_PARSE_FAILE = 5,        /* at command arguments parse is error */
} at_result_t;

/*!
 * @brief define function pointer.
 */
typedef void        (* at_server_init_t )(void);
typedef void        (* at_server_write_t)(char * buf, uint32_t len);
typedef uint32_t    (* at_server_read_t )(char * buf, uint32_t len);
typedef at_result_t (* at_server_test_t )(at_server_write_t write);
typedef at_result_t (* at_server_query_t)(at_server_write_t write);
typedef at_result_t (* at_server_setup_t)(at_server_write_t write, char * args);
typedef at_result_t (* at_server_exec_t )(at_server_write_t write);

/*!
 * @brief This type of structure instance is used to keep the settings.
 * when calling @ref at_server_init() to initialize the at adapter.
 */
typedef struct
{
    at_server_init_t  init;         /* the at server initialization port. */
    at_server_write_t write;        /* the at adapter writer buffer port.*/
    at_server_read_t  read;         /* the at adapter read buffer port. */
    char            * buf;          /* the at adapter receive buffer. */
    uint32_t          buf_size;     /* the at adapter receive buffer size. */
} at_adapter_t;

/*!
 * @brief This type of structure instance is used to keep the settings.
 * when calling @ref at_server_set_cmd_list() to set the at cmd lists.
 */
typedef struct
{
    char            * name;         /* the pointer of at command name. */
    char            * args_expr;    /* the pointer of at command parameter. */
    at_server_test_t  test;         /* query the command parameter format and value range. */
    at_server_query_t query;        /* return the current value of the command parameter. */
    at_server_setup_t setup;        /* set the parameters specified by the user to the corresponding function. */
    at_server_exec_t  exec;         /* execute related operations. */
} at_cmd_t;

/*!
 * @brief the at server structure.
 */
typedef struct
{
    at_adapter_t * adapter;                   /* the pointer of at adapter port. */
    at_cmd_t    ** cmd_list;                  /* the pointer of at command list. */
    uint32_t       cmd_num;                   /* the number of at command list. */
    uint32_t       remaining;                 /* the remaining of the receive buffer. */
    char           end_mark[AT_END_MARK_LEN]; /* the end mark of at command. */
} at_server_t;

/*!
 * @brief Initialize the at server module.
 *
 * @param server Pointer to initialization at server structure. See to @ref at_server_t.
 * @param adapter Pointer to the initialization at aadapter structure. See to @ref at_adapter_t.
 * @return none.
 */
void at_server_init(at_server_t * server, at_adapter_t * adapter);

/*!
 * @brief Set the at server command list.
 *
 * @param server at server instance.
 * @param cmd_list set the at command list. See to @ref at_cmd_t.
 * @param cmd_num the number of the at command.
 * @return none.
 */
void at_server_set_cmd_list(at_server_t * server, at_cmd_t * cmd_list[], uint32_t cmd_num);

/*!
 * @brief Set the at server task.
 * at server start.
 * @param server at server instance.
 * @return none.
 */
void at_server_task(at_server_t * server);

/*!
 * @brief at server write buffer.
 *
 * @param server at server instance.
 * @param buf the data buffer.
 * @param len the data buffer length.
 * @return none.
 */
void at_server_write(at_server_t * server, char * buf, uint32_t len);

/*!
 * @brief at server request arguments parse arguments.
 *
 * @param req_args request arguments.
 * @param req_expr request expression.
 * @return -1: parse arguments failed.
 *          0: parse without match.
 *         >0: The number of arguments successfully paresd.
 */
int at_req_parse_args(const char * req_args, const char * req_expr, ...);

#endif /* __AT_SERVER_H__ */
