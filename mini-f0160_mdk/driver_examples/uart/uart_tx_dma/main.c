/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"
#include "hal_rcc.h"
#include "hal_uart.h"
#include "hal_dma.h"
#include "hal_dma_request.h"

/*
 * Macros.
 */
#define APP_DMA_BUFF_COUNT        4u

/*
 * Variables.
 */
uint32_t app_dma_buff_from[APP_DMA_BUFF_COUNT];
volatile bool app_dma_xfer_done;

/*
 * Declerations.
 */
void    app_uart_init(void);
uint8_t app_uart_getchar(void);
void    app_uart_tx_dma_start(void);


/*
 * Functions.
 */
int main(void)
{
    uint8_t c;

    app_dma_xfer_done = false;

    BOARD_Init();

    app_uart_init();

    while (1)
    {
        c = app_uart_getchar();
        for (uint32_t i = 0u; i < APP_DMA_BUFF_COUNT; i++)
        {
            app_dma_buff_from[i] = c;
        }

        app_uart_tx_dma_start();

        /* Wait while the DMA is busy with sending data through UART. */

        while ( !app_dma_xfer_done )
        {
            BOARD_LedOnTimeout(2u);
            app_dma_xfer_done = false;
        }
    }
}

void app_uart_init(void)
{
    /* Setup the DMA for UART RX. */
    DMA_Channel_Init_Type dma_channel_init;

    dma_channel_init.XferMode = DMA_XferMode_MemoryToPeriph;
    dma_channel_init.ReloadMode = DMA_ReloadMode_AutoReload; /* DMA_AutoReloadMode_Circular */
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_StayAfterXfer;
    dma_channel_init.MemAddrIncMode = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.XferWidth = DMA_XferWidth_32b;
    dma_channel_init.Priority = DMA_Priority_Low;
    dma_channel_init.XferCount = APP_DMA_BUFF_COUNT;
    dma_channel_init.MemAddr = (uint32_t)app_dma_buff_from;
    dma_channel_init.PeriphAddr = UART_GetTxDataRegAddr(BOARD_DEBUG_UART_PORT); /* use tx data register here. */
    DMA_InitChannel(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL, &dma_channel_init);

    /* Enable DMA transfer done interrupt. */
    DMA_EnableChannelInterrupts(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL, DMA_CHN_INT_XFER_DONE, true);
    NVIC_EnableIRQ(BOARD_DMA_UART_TX_IRQn);

    DMA_EnableChannel(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL, true);

    /* Setup the UART. */
    UART_Init_Type uart_init;

    uart_init.ClockFreqHz   = BOARD_DEBUG_UART_FREQ; /* 48mhz, APB2. */
    uart_init.BaudRate      = BOARD_DEBUG_UART_BAUDRATE;
    uart_init.WordLength    = UART_WordLength_8b;
    uart_init.StopBits      = UART_StopBits_1;
    uart_init.Parity        = UART_Parity_None;
    uart_init.XferMode      = UART_XferMode_RxTx;
    uart_init.HwFlowControl = UART_HwFlowControl_None;
    uart_init.XferSignal    = UART_XferSignal_Normal;
    uart_init.EnableSwapTxRxXferSignal = false;
    UART_Init(BOARD_DEBUG_UART_PORT, &uart_init);
    UART_Enable(BOARD_DEBUG_UART_PORT, true);
    UART_EnableDMA(BOARD_DEBUG_UART_PORT, true);
}

void BOARD_DMA_UART_TX_IRQHandler(void)
{
    if (0u != (DMA_CHN_INT_XFER_DONE & DMA_GetChannelInterruptStatus(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL)) )
    {
        app_dma_xfer_done = true;
        DMA_ClearChannelInterruptStatus(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL, DMA_CHN_INT_XFER_DONE);

        /* The DMA channel would be disbaled automatically when the xfer is done. */
        //DMA_EnableChannel(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL, true); /* Enable the DMA channel for the next xfer. */
    }
}

void app_uart_tx_dma_start(void)
{
    DMA_EnableChannel(BOARD_DMA_UART_TX_PORT, BOARD_DMA_UART_TX_CHANNEL, true);
}

uint8_t app_uart_getchar(void)
{
    while ( 0u == (UART_STATUS_RX_DONE & UART_GetStatus(BOARD_DEBUG_UART_PORT)) )
    {}
    return UART_GetData(BOARD_DEBUG_UART_PORT);
}


/* EOF. */
