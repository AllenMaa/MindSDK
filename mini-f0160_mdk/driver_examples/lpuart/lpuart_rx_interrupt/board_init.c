/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "board_init.h"
#include "clock_init.h"
#include "pin_init.h"

#include "hal_rcc.h"
#include "hal_gpio.h"
#include "hal_uart.h"

/*
 * Macros.
 */
#define BOARD_LED_TICK_IN_SYSTICK_TICKS  100u /* 1s. */

/*
 * Variables.
 */
volatile uint32_t led_timeout_ticks;
volatile uint32_t systick_ticks;

/*
* Declerations.
*/
void BOARD_InitLed(void);

/*
* Functions.
*/
void BOARD_Init(void)
{
    BOARD_InitBootClocks();
    BOARD_InitPins();
    BOARD_InitLed();
}

void BOARD_LedOn(void)
{
    GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 0u);
}

void BOARD_LedOff(void)
{
    GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 1u);
}

void BOARD_InitLed(void)
{
    led_timeout_ticks = 0u;
    GPIO_WriteBit(BOARD_LED0_GPIO_PORT, BOARD_LED0_GPIO_PIN, 1u);
}


/* EOF. */
