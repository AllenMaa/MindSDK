/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_init.h"
#include "hal_rcc.h"
#include "hal_gpio.h"

void BOARD_InitPins(void)
{
    GPIO_Init_Type gpio_init;

    /* PA3 - UART2_RX. */
    gpio_init.Pins  = GPIO_PIN_3;
    gpio_init.PinMode  = GPIO_PinMode_In_PullUp;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
    GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_1);

    /* PA2 - UART2_TX. */
    gpio_init.Pins  = GPIO_PIN_2;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
    GPIO_PinAFConf(GPIOA, gpio_init.Pins, GPIO_AF_1);

    /* PA1 - ADC1 channel_1 */
    gpio_init.Pins  = GPIO_PIN_1;
    gpio_init.PinMode  = GPIO_PinMode_In_Analog;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);

    /* PA4 - ADC channel_4 */
    gpio_init.Pins  = GPIO_PIN_4;
    gpio_init.PinMode  = GPIO_PinMode_In_Analog;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);

    /* PA5 - ADC channel_5 */
    gpio_init.Pins  = GPIO_PIN_5;
    gpio_init.PinMode  = GPIO_PinMode_In_Analog;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
}


/* EOF. */
