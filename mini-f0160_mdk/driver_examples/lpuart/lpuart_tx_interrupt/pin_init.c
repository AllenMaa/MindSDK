/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "pin_init.h"
#include "hal_rcc.h"
#include "hal_gpio.h"

/*
 * TXD2 - PA2.
 * RXD2 - PA3.
 */
void BOARD_InitPins(void)
{
    /* PC0 - LPUART_TX. */
    GPIO_Init_Type gpio_init;
    gpio_init.Pins  = GPIO_PIN_0;
    gpio_init.PinMode  = GPIO_PinMode_AF_PushPull;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConf(GPIOC, gpio_init.Pins, GPIO_AF_2);

    /* PC1 - LPUART_RX. */
    gpio_init.Pins  = GPIO_PIN_1;
    gpio_init.PinMode  = GPIO_PinMode_In_Floating;
    gpio_init.Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_PinAFConf(GPIOC, gpio_init.Pins, GPIO_AF_2);
}


/* EOF. */
