/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "at_server.h"


/*
 * Macros.
 */


/*
 * Declerations.
 */
extern const at_cmd_t at_cmd_at;
extern const at_cmd_t at_cmd_led;
/*
 * Variables.
 */
/* set the at command tables. */
const at_cmd_t * at_cmd_list[]=
{
    &at_cmd_at,
    &at_cmd_led
};

extern const at_adapter_t at_adapter;
at_server_t at_server_local;

void at_write(char * buf, uint32_t len);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    /* at server initialization. */
    at_server_init(&at_server_local,(at_adapter_t *)&at_adapter);
    /* set the at command list for at server. */
    at_server_set_cmd_list( &at_server_local, (at_cmd_t **)at_cmd_list, sizeof(at_cmd_list)/sizeof(* at_cmd_list));

    while (1)
    {
        at_server_task(&at_server_local); /* loop the at server task. */
    }
}

/* EOF. */
