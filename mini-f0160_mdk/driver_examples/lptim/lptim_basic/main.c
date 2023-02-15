/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

/*
 * Macros.
 */
#define APP_LPTIM_UPDATE_PERIOD  40000u

/*
 * Variables.
 */

/*
 * Declerations.
 */
void app_lptim_init(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\nlptim_basic example.\r\n");

    /* Setup the timer. */
    app_lptim_init();

    while (1)
    {
    }
}

void app_lptim_init(void)
{
    /* Set the counter work mode. */
    LPTIM_Init_Type lptim_init;
    lptim_init.WorkMode = LPTIM_WorkMode_Timer;
    lptim_init.Prescaler = LPTIM_Prescaler_1;
    lptim_init.Period = APP_LPTIM_UPDATE_PERIOD - 1u; /* 1s, Period = (APP_LPTIM_UPDATE_PERIOD + 1) / (ClockSourceFreqHz / Prescaler). */
    lptim_init.PeriodMode = LPTIM_PeriodMode_Continuous;
    LPTIM_Init(BOARD_LPTIM_PORT, &lptim_init);

    /* Enable interrupt. */
    LPTIM_EnableInterrupts(BOARD_LPTIM_PORT, LPTIM_INT_COUNTER_OVERFLOW, true);
    NVIC_EnableIRQ(BOARD_LPTIM_IRQn);

    /* Start the counter. */
    LPTIM_Start(BOARD_LPTIM_PORT);
}

void BOARD_LPTIM_IRQHandler(void)
{
    LPTIM_Stop(BOARD_LPTIM_PORT);
    uint32_t flags = LPTIM_GetInterruptStatus(BOARD_LPTIM_PORT);
    if ( 0u != (flags & LPTIM_STATUS_COUNTER_OVERFLOW) ) /* Check overflow status. */
    {
        putchar('*');
    }
    LPTIM_ClearInterruptStatus(BOARD_LPTIM_PORT, flags);
    LPTIM_Start(BOARD_LPTIM_PORT);
}

/* EOF. */
