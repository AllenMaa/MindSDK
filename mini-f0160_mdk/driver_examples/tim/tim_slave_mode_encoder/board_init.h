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
#include "hal_tim.h"
#include "hal_gpio.h"
#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ

/* TIM1. */
#define BOARD_TIM_PORT              (TIM_Type *)TIM1
#define BOARD_TIM_IRQn              TIM1_BRK_UP_TRG_COM_IRQn
#define BOARD_TIM_IRQHandler        TIM1_BRK_UP_TRG_COM_IRQHandler
#define BOARD_TIM_FREQ              CLOCK_APB2_FREQ
#define BOARD_TIM_CHN_1             TIM_CHN_1
#define BOARD_TIM_CHN_2             TIM_CHN_2
#define BOARD_TIM_STATUS_CHN_EVENT  TIM_STATUS_CHN1_EVENT
#define BOARD_TIM_CHN_1_PIN         GPIO_PIN_5
#define BOARD_TIM_CHN_2_PIN         GPIO_PIN_6
#define BOARD_TIM_CHN_PORT          GPIOA

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */

