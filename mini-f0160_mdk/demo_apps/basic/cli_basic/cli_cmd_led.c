/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "embedded_cli.h"
#include "board_init.h"

void cli_led_binding(EmbeddedCli *cli, char *args, void *context);

const CliCommandBinding cli_led_cmd_binding = {
    .name           = "led",
    .help           = "Usage: led <on/off> \r\n\tSet LED onoff.",
    .tokenizeArgs   = true,
    .context        = NULL,
    .binding        = cli_led_binding,
};

/* cli cmd func, when received "hello" cmd, call this func. */
void cli_led_binding(EmbeddedCli *cli, char *args, void *context)
{
    (void) context;

    /* get cli token num. */
    uint16_t argc = embeddedCliGetTokenCount(args);
    if (argc != 1)
    {
        embeddedCliPrint(cli, "invalid arguments.");
        return;
    }

    /* get first token. */
    const char* state = embeddedCliGetToken(args, 1);

    if (strcmp(state, "on") == 0)
    {
        led_on();
    }
    else if (strcmp(state, "off") == 0)
    {
        led_off();
    }
    else
    {
        embeddedCliPrint(cli, "invalid arguments.");
    }
}

/* EOF. */
