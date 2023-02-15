/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

#define APP_TIM_STEP_FREQ      1000000u /* 1MHz resolution. */
#define APP_TIM_UPDATE_PERIOD  1000u    /* 1ms period scale, the num of steps. */

#define APP_TIM_PWM_NUM   8u
uint16_t app_tim_pwm_val[APP_TIM_PWM_NUM] =
{
    (APP_TIM_UPDATE_PERIOD >> 3u) * 1u, /* 1/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 2u, /* 2/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 3u, /* 3/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 4u, /* 4/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 5u, /* 5/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 6u, /* 6/8. */
    (APP_TIM_UPDATE_PERIOD >> 3u) * 7u, /* 7/8. */
    APP_TIM_UPDATE_PERIOD,              /* 8/8. */
};

void app_tim_init(void);

/*
 * Functions.
 */

int main(void)
{
    BOARD_Init();
    printf("\r\ntim_output_compare_pwm.\r\n");

    /* Setup the timer. */
    app_tim_init();

    while (1)
    {
        for (uint32_t i = 0u; i < APP_TIM_PWM_NUM; i++)
        {
            getchar();
            
            /* Update duty cycle. */
            TIM_PutChannelValue(BOARD_TIM_PORT, BOARD_TIM_CHANNEL, app_tim_pwm_val[i]);
            printf("PWM value: %u\r\n", (unsigned)app_tim_pwm_val[i]);
        }
    }
}

/* Setup the timer. */
void app_tim_init(void)
{
    /* Setup the counter counting step. */
    TIM_Init_Type tim_init;
    tim_init.ClockFreqHz = BOARD_TIM_FREQ;
    tim_init.StepFreqHz = APP_TIM_STEP_FREQ;
    tim_init.Period = APP_TIM_UPDATE_PERIOD - 1u; /* the counter would return to the base on next step. */
    tim_init.EnablePreloadPeriod = false; /* no need preload, load period value immediately. */
    tim_init.PeriodMode = TIM_PeriodMode_Continuous;
    tim_init.CountMode = TIM_CountMode_Increasing;
    TIM_Init(BOARD_TIM_PORT, &tim_init);

    /* Setup the PWM output channel. */
    TIM_OutputCompareConf_Type tim_out_conf;
    tim_out_conf.ChannelValue = 0u;
    tim_out_conf.EnableFastOutput = false;
    tim_out_conf.EnablePreLoadChannelValue = false; /* disable preload, load channel value immediately. */
    tim_out_conf.RefOutMode = TIM_OutputCompareRefOut_FallingEdgeOnMatch;
    tim_out_conf.ClearRefOutOnExtTrigger = false;
    tim_out_conf.PinPolarity = TIM_PinPolarity_Rising;
    TIM_EnableOutputCompare(BOARD_TIM_PORT, BOARD_TIM_CHANNEL, &tim_out_conf);

    /* Start the output compare, only available for the TIM peripheral with this feature. */
    TIM_EnableOutputCompareSwitch(BOARD_TIM_PORT, true);

    /* Start the counter. */
    TIM_Start(BOARD_TIM_PORT);
}

/* EOF. */

