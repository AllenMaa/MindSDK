/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Macros.
 */
#define BOARD_AT_BUF_SIZE   64u  /* the at server receive buffer size. */

/*
 * Variables.
 */

static char     at_adapter_buf[BOARD_AT_BUF_SIZE]; /* the buffer for at server. */
static uint8_t  rbuf_buf[BOARD_AT_BUF_SIZE]; /* the buffer for rbuf. */
static rbuf_handler_t rbuf_handler; /* rbuf handler. */

/*
 * Declerations.
 */

static void     at_init(void);
static uint32_t at_read(char * buf, uint32_t len);
static void     at_write(char * buf, uint32_t len);

/* initialize the at adapter. */
const at_adapter_t at_adapter =
{
    .init       = at_init,
    .read       = at_read,
    .write      = at_write,
    .buf        = at_adapter_buf,
    .buf_size   = BOARD_AT_BUF_SIZE,
};

/*
* Functions.
*/

/* init func. */
static void at_init(void)
{
    /* init rbuf. */
    rbuf_init(&rbuf_handler, rbuf_buf, sizeof(rbuf_buf) );

    /* init at uart port. */
    UART_Init_Type uart_init;
    uart_init.ClockFreqHz   = BOARD_AT_UART_FREQ;
    uart_init.BaudRate      = BOARD_AT_UART_BAUDRATE;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;
    UART_Init(BOARD_AT_UART_PORT, &uart_init);
    UART_Enable(BOARD_AT_UART_PORT, true);
    UART_EnableInterrupts(BOARD_AT_UART_PORT, UART_INT_RX_DONE, true);
    NVIC_EnableIRQ(BOARD_AT_UART_IRQn);
}

/* read data from rbuf. */
static uint32_t at_read(char * buf, uint32_t len)
{
    uint32_t read_cnt = 0u;
    for (; read_cnt < len; read_cnt++)
    {
        if (rbuf_is_empty(&rbuf_handler) )
        {
            break;
        }
        buf[read_cnt] = rbuf_output(&rbuf_handler);
    }
    return read_cnt;
}

/* write data by uart. */
static void at_write(char * buf, uint32_t len)
{
    for (uint32_t i = 0u; i < len; i++)
    {
        while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(BOARD_AT_UART_PORT)) )
        {}
        UART_PutData(BOARD_AT_UART_PORT,buf[i]);
    }
}

/* the interrupt handler of uart. */
void BOARD_AT_UART_IRQHandler(void)
{
    uint32_t flag = UART_GetInterruptStatus(BOARD_AT_UART_PORT);

    if ( 0u!= (UART_INT_RX_DONE & flag) )
    {
        /* get byte. */
        uint8_t data = UART_GetData(BOARD_AT_UART_PORT);

        /* echo. */
        at_write((char *)&data, 1u);

        /* in queue. */
        rbuf_input(&rbuf_handler, data);
    }
    UART_ClearInterruptStatus(BOARD_AT_UART_PORT, flag);
}

/* EOF. */
