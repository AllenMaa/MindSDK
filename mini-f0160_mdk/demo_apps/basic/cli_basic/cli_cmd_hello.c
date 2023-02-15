/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "embedded_cli.h"
#include "stdio.h"

void cli_hello_binding(EmbeddedCli *cli, char *args, void *context);

const CliCommandBinding cli_hello_cmd_binding = {
    .name           = "hello",
    .help           = "Usage: hello \r\n\tPrint \"Hello, World\" on terminal.",
    .tokenizeArgs   = true,
    .context        = NULL,
    .binding        = cli_hello_binding,
};

/* cli cmd func, when received "hello" cmd, call this func. */
void cli_hello_binding(EmbeddedCli *cli, char *args, void *context)
{
    (void) context;

    embeddedCliPrint(cli, "Hello World.\r\n");
}

/* EOF. */
