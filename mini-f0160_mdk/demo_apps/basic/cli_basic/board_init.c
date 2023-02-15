/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "board_init.h"
#include "hal_gpio.h"

/*
* Definitions.
*/

/*
* Declerations.
*/

/*
* Functions.
*/
void BOARD_Init(void)
{
    BOARD_InitBootClocks();
    BOARD_InitPins();
}

void led_on(void)
{
    GPIO_ClearBits(BOARD_LED_GPIO_PORT, BOARD_LED_GPIO_PIN);
}

void led_off(void)
{
    GPIO_SetBits(BOARD_LED_GPIO_PORT, BOARD_LED_GPIO_PIN);
}

/* EOF. */
