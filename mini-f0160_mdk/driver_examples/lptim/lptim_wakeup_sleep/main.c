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
#define APP_LPTIM_UPDATE_PERIOD  4000u

/*
 * Variables.
 */

/*
 * Declerations.
 */
void app_lptim_init(void);
void app_lptim_entry_sleep(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\nlptim_wakeup_sleep example.\r\n");
    printf("press trigger input pin to wake up MCU from sleep mode. \r\n");

    /* Setup the timer. */
    app_lptim_init();

    /* Entry sleep mode. */
    app_lptim_entry_sleep();

    /* Wait for wake up. */
    while (1)
    {
        printf("Wake up from sleep mode.\r\n");
        getchar();
    }
}

void app_lptim_init(void)
{
    /* Set the counter work mode. */
    LPTIM_Init_Type lptim_init;
    lptim_init.WorkMode = LPTIM_WorkMode_WakeUpLowPower;
    lptim_init.Prescaler = LPTIM_Prescaler_1;
    lptim_init.Period = APP_LPTIM_UPDATE_PERIOD - 1u; /* 100ms, Period = (APP_LPTIM_UPDATE_PERIOD + 1) / (ClockSourceFreqHz / Prescaler). */
    lptim_init.PeriodMode = LPTIM_PeriodMode_Continuous;
    LPTIM_Init(BOARD_LPTIM_PORT, &lptim_init);

    /* Enable pin trigger input. */
    LPTIM_TriggerInConf_Type lptim_trigger_conf;
    lptim_trigger_conf.Channel = LPTIM_TriggerInChannel_Pin;
    lptim_trigger_conf.EnableFilter = true;
    lptim_trigger_conf.TriggerInPolarity = LPTIM_TriggerInPolarity_Falling;
    LPTIM_EnableTriggerIn(BOARD_LPTIM_PORT, &lptim_trigger_conf);

    /* Enable interrupt. */
    LPTIM_EnableInterrupts(BOARD_LPTIM_PORT, LPTIM_INT_COUNTER_OVERFLOW, true);
    NVIC_EnableIRQ(BOARD_LPTIM_IRQn);

    /* Start the counter. */
    LPTIM_Start(BOARD_LPTIM_PORT);
}

void app_lptim_entry_sleep(void)
{
    __WFI();
}

void BOARD_LPTIM_IRQHandler(void)
{
    LPTIM_Stop(BOARD_LPTIM_PORT);
    uint32_t flags = LPTIM_GetInterruptStatus(BOARD_LPTIM_PORT);
    if ( 0u != (flags & LPTIM_STATUS_COUNTER_OVERFLOW) ) /* Check overflow status. */
    {
    }
    LPTIM_ClearInterruptStatus(BOARD_LPTIM_PORT, flags);
}

/* EOF. */
