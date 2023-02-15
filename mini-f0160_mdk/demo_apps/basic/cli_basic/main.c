/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "embedded_cli.h"

/*
 * Macros.
 */

#define APP_CLI_BUF_SIZE        512
#define APP_CLI_RX_BUF_SIZE     16
#define APP_CLI_CMD_BUF_SIZE    64
#define APP_CLI_HISTORY_SIZE    32

/*
 * Variables.
 */

CLI_UINT      cli_buf[BYTES_TO_CLI_UINTS(APP_CLI_BUF_SIZE)];
EmbeddedCli * app_cli;

extern const CliCommandBinding cli_hello_cmd_binding;
extern const CliCommandBinding cli_led_cmd_binding;

/* set the cli cmd. */
const CliCommandBinding *cli_cmd_binging_list[] =
{
    &cli_hello_cmd_binding,
    &cli_led_cmd_binding
};

/*
 * Declerations.
 */

void cli_init(void);

void cli_port_init(void);
char cli_port_getchar(void);
void cli_port_putchar(EmbeddedCli *cli, char c);

/*
 * Functions.
 */
int main(void)
{
    uint8_t ch;

    BOARD_Init();

    /* init cli. */
    cli_port_init();
    cli_init();

    while (1)
    {
        /* get received char. */
        ch = cli_port_getchar();
        while(ch != 0)
        {
            embeddedCliReceiveChar(app_cli, ch);
            ch = cli_port_getchar();
        }

        /* cli process. */
        embeddedCliProcess(app_cli);
    }
}

void cli_init(void)
{
    EmbeddedCliConfig *cli_conf = embeddedCliDefaultConfig();
    cli_conf->cliBuffer         = cli_buf;
    cli_conf->cliBufferSize     = APP_CLI_BUF_SIZE;
    cli_conf->rxBufferSize      = APP_CLI_RX_BUF_SIZE;
    cli_conf->cmdBufferSize     = APP_CLI_CMD_BUF_SIZE;
    cli_conf->historyBufferSize = APP_CLI_HISTORY_SIZE;
    cli_conf->maxBindingCount   = sizeof(cli_cmd_binging_list) / sizeof(*cli_cmd_binging_list);

    if (embeddedCliRequiredSize(cli_conf) > APP_CLI_BUF_SIZE)
    {
        return; /* buf size not enough. */
    }

    /* create cli. */
    app_cli = embeddedCliNew(cli_conf);

    /* set write char func. */
    app_cli->writeChar = cli_port_putchar;

    /* add cli cmd. */
    for (uint32_t i = 0; i < cli_conf->maxBindingCount; i++)
    {
        embeddedCliAddBinding(app_cli, *cli_cmd_binging_list[i]);
    }
}


/* EOF. */
