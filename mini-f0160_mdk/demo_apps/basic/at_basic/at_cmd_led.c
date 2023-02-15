/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "at_server.h"
#include "board_init.h"

/*
 * Macros.
 */

#define AT_CMD_BUF_SIZE     64u  /* at command buffer size. */

/*
 * Declerations.
 */

/* to query the parameter format and value range for AT+LED command. */
at_result_t at_cmd_led_test(at_server_write_t write);

/* to return command parameters. */
at_result_t at_cmd_led_query(at_server_write_t write);

/* to set user-specified parameters into the corresponding function. */
at_result_t at_cmd_led_setup(at_server_write_t write, char * args);

/* to perform related operations. */
at_result_t at_cmd_led_exec(at_server_write_t write);


/*
 * Variables.
 */

const at_cmd_t at_cmd_led =
{
    .name = "AT+LED",
    .args_expr = "<value>",
    .test  = at_cmd_led_test,  /* AT+LED=?    */
    .query = at_cmd_led_query, /* AT+LED?     */
    .setup = at_cmd_led_setup, /* AT+LED=1, 0 */
    .exec  = at_cmd_led_exec   /* AT+LED      */
};

/*
 * Functions.
 */

/* when sending AT+LED=? command will call this function. to qurey the format and the range of paramter of the command. */
at_result_t at_cmd_led_test(at_server_write_t write)
{
    char buf[AT_CMD_BUF_SIZE];
    sprintf(buf, "AT+LED=<value>, value=0,1\r\n");
    write(buf, strlen(buf));

    return AT_RESULT_OK;
}

/* when sending AT+LED? command will call this function. to query the current value of the command. */
at_result_t at_cmd_led_query(at_server_write_t write)
{
    char buf[AT_CMD_BUF_SIZE];

    sprintf(buf, "+LED=%d\r\n", GPIO_ReadOutDataBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN));
    write(buf, strlen(buf));

    return AT_RESULT_OK;
}

/* when sending AT+LED=<value>, the value can be 0 or 1 or other, will call this function. */
at_result_t at_cmd_led_setup(at_server_write_t write, char * args)
{
    char buf[AT_CMD_BUF_SIZE];
    uint32_t param; /* the command parameter. */

    if (1u == at_req_parse_args(args, "=%d", &param))
    {
        if (param == 1)
        {
            GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 1u);
        }

        else if (param == 0)
        {
            GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 0u);
        }

        if (param == GPIO_ReadOutDataBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN)) /* check whether the corresponding function is correctly executed. */
        {
            sprintf(buf, "OK\r\n");
        }

        else
        {
            sprintf(buf, "ERROR\r\n");
        }
    }

    else
    {
        sprintf(buf, "ERROR \r\n");
    }
    write(buf, strlen(buf));

    return AT_RESULT_OK;
}

/* when sending AT+LED command will call this function. to exectue led initialization. */
at_result_t at_cmd_led_exec(at_server_write_t write)
{
    char buf[AT_CMD_BUF_SIZE];

    /* LED initialize. */
    GPIO_Init_Type gpio_init;
    gpio_init.Pins  = BOARD_LED0_GPIO_PIN;
    gpio_init.PinMode  = GPIO_PinMode_Out_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(BOARD_LED0_GPIO_PORT, &gpio_init);
    GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 1u);
    sprintf(buf, "OK\r\n");
    write(buf, strlen(buf));

    return AT_RESULT_OK;
}
/* EOF. */
