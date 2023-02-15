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
#define APP_LPTIM_UPDATE_PERIOD 40U
#define APP_LPTIM_PWM_NUM   8u

/*
 * Variables.
 */
uint16_t app_lptim_pwm_val[APP_LPTIM_PWM_NUM] =
{
    (APP_LPTIM_UPDATE_PERIOD >> 3u) * 1u, /* 1/8. */
    (APP_LPTIM_UPDATE_PERIOD >> 3u) * 2u, /* 2/8. */
    (APP_LPTIM_UPDATE_PERIOD >> 3u) * 3u, /* 3/8. */
    (APP_LPTIM_UPDATE_PERIOD >> 3u) * 4u, /* 4/8. */
    (APP_LPTIM_UPDATE_PERIOD >> 3u) * 5u, /* 5/8. */
    (APP_LPTIM_UPDATE_PERIOD >> 3u) * 6u, /* 6/8. */
    (APP_LPTIM_UPDATE_PERIOD >> 3u) * 7u, /* 7/8. */
    APP_LPTIM_UPDATE_PERIOD,              /* 8/8. */
};

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
    printf("\r\nlptim_output_pwm example.\r\n");

    /* Setup the timer. */
    app_lptim_init();

    while (1)
    {
       for (uint32_t i = 0u; i < APP_LPTIM_PWM_NUM; i++)
       {
           getchar();

           /* Update duty cycle. */
           LPTIM_Stop(BOARD_LPTIM_PORT);
           LPTIM_SetCompareValue(BOARD_LPTIM_PORT, app_lptim_pwm_val[i]);
           LPTIM_Start(BOARD_LPTIM_PORT);
           printf("PWM value: %u\r\n", (unsigned)app_lptim_pwm_val[i]);
       }
    }
}

void app_lptim_init(void)
{
    /* Set the counter work mode. */
    LPTIM_Init_Type lptim_init;
    lptim_init.WorkMode = LPTIM_WorkMode_Timer;
    lptim_init.Prescaler = LPTIM_Prescaler_1;
    lptim_init.Period = APP_LPTIM_UPDATE_PERIOD - 1u; /* 1ms, Period = (APP_LPTIM_UPDATE_PERIOD + 1) / (ClockSourceFreqHz / Prescaler). */
    lptim_init.PeriodMode = LPTIM_PeriodMode_Continuous;
    LPTIM_Init(BOARD_LPTIM_PORT, &lptim_init);

    /* Set output waveform parameters. */
    LPTIM_OutWaveConf_Type lptim_wave_conf;
    lptim_wave_conf.Wave = LPTIM_OutWave_PWM;
    lptim_wave_conf.OutPolarity = LPTIM_OutPolarity_Falling;
    LPTIM_EnableOutWave(BOARD_LPTIM_PORT, &lptim_wave_conf);
}

/* EOF. */
