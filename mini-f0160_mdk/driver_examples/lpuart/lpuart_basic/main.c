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

/*
 * Variables.
 */

/*
 * Declerations.
 */
void app_lpuart_init(void);
void app_lpuart_putchar(uint8_t c);
void app_lpuart_putstr(uint8_t *str);
uint8_t app_lpuart_getchar(void);
void app_soft_delay(uint32_t delay);

/*
 * Functions.
 */
int main(void)
{
    uint8_t c;
    BOARD_Init();

    app_lpuart_init();
    app_lpuart_putstr((uint8_t *)"\r\nlpuart_basic example.\r\n");

    while (1)
    {
        c = app_lpuart_getchar();
        app_lpuart_putchar(c);
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

    LPUART_Init(BOARD_DEBUG_LPUART_PORT, &lpuart_init);
    LPUART_EnableTx(BOARD_DEBUG_LPUART_PORT, true);
    app_soft_delay(100u);
    LPUART_EnableRx(BOARD_DEBUG_LPUART_PORT, true);
}

void app_lpuart_putchar(uint8_t c)
{
    while ( 0u == (LPUART_STATUS_TX_EMPTY & LPUART_GetStatus(BOARD_DEBUG_LPUART_PORT) ) )
    {
    }
    LPUART_PutData(BOARD_DEBUG_LPUART_PORT, (uint8_t)(c));
}

uint8_t app_lpuart_getchar(void)
{
    while ( 0u == (LPUART_STATUS_RX_FULL & LPUART_GetStatus(BOARD_DEBUG_LPUART_PORT) ) )
    {
    }
    return LPUART_GetData(BOARD_DEBUG_LPUART_PORT);
}

void app_lpuart_putstr(uint8_t *str)
{
    while ((*str) != '\0')
    {
        app_lpuart_putchar(*str);
        str++;
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
