/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>
#include "board_init.h"
#include "hal_lpuart.h"

/*
 * Definitions.
 */
#define APP_LPUART_TX_BUFF_LEN 4u

/*
 * Variables.
 */
volatile uint8_t  app_lpuart_tx_buff[APP_LPUART_TX_BUFF_LEN];
uint32_t app_lpuart_tx_buff_idx = 0u;

/*
 * Declerations.
 */
void app_lpuart_init(void);
void app_lpuart_putstr_int(uint8_t c);
uint8_t app_lpuart_getchar(void);
void app_lpuart_tx_isr_hook(void);
void app_soft_delay(uint32_t delay);

/*
 * Functions.
 */
int main(void)
{
    uint8_t c;
    BOARD_Init();

    app_lpuart_init();
    
    while(1)
    {
        c = app_lpuart_getchar();
        app_lpuart_putstr_int(c);
    }
}

void app_lpuart_init(void)
{
    LPUART_Init_Type lpuart_init;
    
    lpuart_init.BaudRate    = BOARD_DEBUG_LPUART_BAUDRATE;
    lpuart_init.ClockSource = LPUART_ClockSource_LSE;    /* LSE clock frequency is 32.768KHz. */
    lpuart_init.Parity      = LPUART_Parity_None;
    lpuart_init.StopBits    = LPUART_StopBits_1;
    lpuart_init.WordLength  = LPUART_WordLength_8;

    LPUART_Init(BOARD_DEBUG_LPUART_PORT, &lpuart_init);
    NVIC_EnableIRQ(BOARD_DEBUG_LPUART_IRQn);

    LPUART_EnableRx(BOARD_DEBUG_LPUART_PORT, true);
    app_soft_delay(100u);
    LPUART_EnableTx(BOARD_DEBUG_LPUART_PORT, true);
}

uint8_t app_lpuart_getchar(void)
{
    while ( 0u == (LPUART_STATUS_RX_FULL & LPUART_GetStatus(BOARD_DEBUG_LPUART_PORT) ) )
    {
    }
    return LPUART_GetData(BOARD_DEBUG_LPUART_PORT);
}

void app_lpuart_putstr_int(uint8_t c)
{
    /* prepare the buffer. */
    for (uint32_t i = 0u; i < APP_LPUART_TX_BUFF_LEN; i++)
    {
        app_lpuart_tx_buff[i] = c;
    }
    app_lpuart_tx_buff_idx = 0u;

    /* enable the tx interrupt to transmit the buffer. */
    LPUART_EnableInterrupts(BOARD_DEBUG_LPUART_PORT, LPUART_STATUS_INTSTATUS_TX_EMPTY, true);
}

void app_lpuart_tx_isr_hook(void)
{
    if ( (0u != (LPUART_STATUS_INTSTATUS_TX_EMPTY & LPUART_GetEnabledInterrupts(BOARD_DEBUG_LPUART_PORT) ) )
        && (0u != (LPUART_STATUS_INTSTATUS_TX_EMPTY & LPUART_GetStatus(BOARD_DEBUG_LPUART_PORT) ) ) )
    {
        if (app_lpuart_tx_buff_idx != APP_LPUART_TX_BUFF_LEN)
        {
            LPUART_ClearStatus(BOARD_DEBUG_LPUART_PORT, LPUART_STATUS_INTSTATUS_TX_EMPTY);
            LPUART_PutData(BOARD_DEBUG_LPUART_PORT, app_lpuart_tx_buff[app_lpuart_tx_buff_idx]);
            app_lpuart_tx_buff_idx++;
        }
        else
        {
            LPUART_EnableInterrupts(BOARD_DEBUG_LPUART_PORT, LPUART_STATUS_INTSTATUS_TX_EMPTY, false);
        }
    }
}

void BOARD_DEBUG_LPUART_IRQHandler()
{
    app_lpuart_tx_isr_hook();
}

void app_soft_delay(uint32_t delay)
{
    for(uint32_t i = 0; i < delay; i++)
    {
        for(uint32_t j = 0; j < 10000; j++)
        {
            __NOP();
        }
    }
}

/* EOF. */
