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
 * Macros.
 */
#define APP_LPUART_RX_BUFF_LEN 1u
uint32_t app_lpuart_rxdone_flag = false;

/*
 * Variables.
 */
volatile uint8_t  app_lpuart_rx_buff[APP_LPUART_RX_BUFF_LEN];
volatile uint32_t app_lpuart_rx_buff_idx = 0u;

/*
 * Declerations.
 */
void app_lpuart_init(void);
void app_lpuart_rx_isr_hook(void);
void app_soft_delay(uint32_t delay);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    app_lpuart_init();
    while (1)
    {
        if (app_lpuart_rxdone_flag == true)
        {
            BOARD_LedOn();
            app_soft_delay(500u);
            BOARD_LedOff();
            app_lpuart_rxdone_flag = false;
        }
    }
}

void app_lpuart_init(void)
{
    LPUART_Init_Type lpuart_init;
    
    lpuart_init.BaudRate    = BOARD_DEBUG_LPUART_BAUDRATE;
    lpuart_init.ClockSource = LPUART_ClockSource_LSE;  /* LSE clock frequency is 32.768KHz. */
    lpuart_init.Parity      = LPUART_Parity_None;
    lpuart_init.StopBits    = LPUART_StopBits_1;
    lpuart_init.WordLength  = LPUART_WordLength_8;

    app_lpuart_rxdone_flag = false;

    LPUART_Init(BOARD_DEBUG_LPUART_PORT, &lpuart_init);

    LPUART_EnableInterrupts(BOARD_DEBUG_LPUART_PORT, LPUART_STATUS_INTSTATUS_RX_DONE, true);
    LPUART_SetRxInterruptAF(BOARD_DEBUG_LPUART_PORT, LPUART_RxInterruptAF_Alt1);
    NVIC_EnableIRQ(BOARD_DEBUG_LPUART_IRQn);

    LPUART_EnableTx(BOARD_DEBUG_LPUART_PORT, true);
    app_soft_delay(100u);
    LPUART_EnableRx(BOARD_DEBUG_LPUART_PORT, true);
}

void BOARD_DEBUG_LPUART_IRQHandler(void)
{
    if ( (0u != (LPUART_STATUS_INTSTATUS_RX_DONE & LPUART_GetEnabledInterrupts(BOARD_DEBUG_LPUART_PORT) ) )
        && (0u != (LPUART_STATUS_INTSTATUS_RX_DONE & LPUART_GetStatus(BOARD_DEBUG_LPUART_PORT) ) ) )
    {
        app_lpuart_rx_buff[app_lpuart_rx_buff_idx] = LPUART_GetData(BOARD_DEBUG_LPUART_PORT);
        app_lpuart_rxdone_flag = true;
        LPUART_ClearStatus(BOARD_DEBUG_LPUART_PORT, LPUART_STATUS_INTSTATUS_RX_DONE);
    }
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
