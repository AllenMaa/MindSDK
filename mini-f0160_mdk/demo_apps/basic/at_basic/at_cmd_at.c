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
#define AT_CMD_BUF_SIZE     64u   /* at command buffer size. */

/*
 * Declerations.
 */

/* to perform related operations, wait for at server ready. */
at_result_t at_cmd_at_exec(at_server_write_t write);


/*
 * Variables.
 */

const at_cmd_t at_cmd_at =
{
    .name = "AT",
    .args_expr = NULL,
    .test = NULL,
    .query = NULL,
    .setup = NULL,
    .exec = at_cmd_at_exec
};

/*
 * Functions.
 */

/* at execute function, when sending AT command, call this function.*/
at_result_t at_cmd_at_exec(at_server_write_t write)
{
    char buf[AT_CMD_BUF_SIZE];

    sprintf(buf, "READY\r\n");
    write(buf, strlen(buf));

    return AT_RESULT_OK;
}

/* EOF. */
