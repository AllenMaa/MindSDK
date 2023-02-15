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
* Definitions.
*/

/*
* Declerations.
*/
void BOARD_InitDebugConsole(void);

/*
* Functions.
*/
void BOARD_Init(void)
{
    BOARD_InitBootClocks();
    BOARD_InitPins();
}

/* EOF. */
