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
#include "hal_rcc.h"
#include "hal_uart.h"
#include "hal_exti.h"
#include "hal_syscfg.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ

/*SYSCFG*/
#define BOARD_SYSCFG_EXTIPORT        SYSCFG_EXTIPort_GPIOC
#define BOARD_SYSCFG_EXTILINE        SYSCFG_EXTILine_11

/*EXTI*/
#define BOARD_EXTI_PORT              EXTI
#define BOARD_EXTI_LINE              EXTI_LINE_11
#define BOARD_EXTI_IRQN              EXTI15_4_IRQn
#define BOARD_EXTI_IRQHandler        EXTI15_4_IRQHandler

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
