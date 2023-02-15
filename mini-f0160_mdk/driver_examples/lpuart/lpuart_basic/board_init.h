/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>
#include <stdint.h>

#include "hal_common.h"

#include "clock_init.h"

/* DEBUG UART. */
/* DEBUG LPUART. */
#define BOARD_DEBUG_LPUART_PORT        LPUART
#define BOARD_DEBUG_LPUART_BAUDRATE    LPUART_Baudrate_9600

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */

