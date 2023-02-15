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
#define APP_LPTIM_UPDATE_PERIOD  3u

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
    printf("\r\nlptim_external_trigger_input example.\r\n");

    /* Setup the timer. */
    app_lptim_init();

    printf("press input key to lead external trigger input event and counter overflow event happen.\r\n");

    while (1)
    {
        getchar();
        printf("counter:%u\r\n", (unsigned)LPTIM_GetCounterValue(BOARD_LPTIM_PORT) );
    }
}

void app_lptim_init(void)
{
    /* Set the counter work mode. */
    LPTIM_Init_Type lptim_init;
    lptim_init.WorkMode = LPTIM_WorkMode_Trigger;
    lptim_init.Period = APP_LPTIM_UPDATE_PERIOD - 1u; /* Every APP_LPTIM_UPDATE_PERIOD arrive will lead a overflow interrupt. */
    lptim_init.PeriodMode = LPTIM_PeriodMode_Continuous;
    LPTIM_Init(BOARD_LPTIM_PORT, &lptim_init);

    /* Enable pin trigger input. */
    LPTIM_TriggerInConf_Type lptim_trigger_conf;
    lptim_trigger_conf.Channel = LPTIM_TriggerInChannel_Pin;
    lptim_trigger_conf.EnableFilter = true;
    lptim_trigger_conf.TriggerInPolarity = LPTIM_TriggerInPolarity_Rising;
    LPTIM_EnableTriggerIn(BOARD_LPTIM_PORT, &lptim_trigger_conf);

    /* Enable interrupts. */
    LPTIM_EnableInterrupts(BOARD_LPTIM_PORT, LPTIM_INT_TRIGGER_INPUT, true);
    LPTIM_EnableInterrupts(BOARD_LPTIM_PORT, LPTIM_INT_COUNTER_OVERFLOW, true);
    NVIC_EnableIRQ(BOARD_LPTIM_IRQn);

    /* Start the counter. */
    LPTIM_Start(BOARD_LPTIM_PORT);
}

void BOARD_LPTIM_IRQHandler(void)
{
    uint32_t flags = LPTIM_GetInterruptStatus(BOARD_LPTIM_PORT);

    if ( 0u != (flags & LPTIM_STATUS_TRIGGER_INPUT) ) /* Check trigger status. */
    {
        printf("trigger input event happens.\r\n");
    }
    if ( 0u != (flags & LPTIM_STATUS_COUNTER_OVERFLOW) ) /* Check overflow status. */
    {
        printf("counter overflow event happens.\r\n");
    }
    LPTIM_ClearInterruptStatus(BOARD_LPTIM_PORT, flags);
}

/* EOF. */
