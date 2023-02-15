/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "board_init.h"

#include "rbuf.h"
#include "embedded_cli.h"

#define RBUF_BUF_SIZE   128

static rbuf_handler_t recv_rbuf_handler;
static uint8_t        recv_rbuf_buf[RBUF_BUF_SIZE];

/* init cli port. */
void cli_port_init(void)
{
    /* init rbuf. */
    rbuf_init(&recv_rbuf_handler, recv_rbuf_buf, RBUF_BUF_SIZE);

    /* init uart. */
    UART_Init_Type uart_init;

    uart_init.ClockFreqHz   = BOARD_CLI_UART_FREQ;
    uart_init.BaudRate      = BOARD_CLI_UART_BAUDRATE;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;
    UART_Init(BOARD_CLI_UART_PORT, &uart_init);
    UART_Enable(BOARD_CLI_UART_PORT, true);

    /* enable uart rx interrupt. */
    UART_EnableInterrupts(BOARD_CLI_UART_PORT, UART_INT_RX_DONE, true);
    NVIC_EnableIRQ(BOARD_CLI_UART_IRQn);
}

/* get char. */
char cli_port_getchar(void)
{
    char ret = 0;
    NVIC_DisableIRQ(BOARD_CLI_UART_IRQn);
    if (!rbuf_is_empty(&recv_rbuf_handler) )
    {
        ret = rbuf_output(&recv_rbuf_handler);
    }
    NVIC_EnableIRQ(BOARD_CLI_UART_IRQn);
    return ret;
}

/* put char. */
void cli_port_putchar(EmbeddedCli *cli, char c)
{
    (void) cli;
    while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(BOARD_CLI_UART_PORT)) )
    {}
    UART_PutData(BOARD_CLI_UART_PORT, (uint8_t)(c));
}

/* uart interrupt handler. */
void BOARD_CLI_UART_IRQHandler(void)
{
    uint32_t flags = UART_GetInterruptStatus(BOARD_CLI_UART_PORT);
    if (0 != (flags & UART_INT_RX_DONE))
    {
        rbuf_input(&recv_rbuf_handler, UART_GetData(BOARD_CLI_UART_PORT));
    }
    UART_ClearInterruptStatus(BOARD_CLI_UART_PORT, flags);
}

/* EOF. */
