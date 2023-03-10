/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>

#include "hal_common.h"
#include "hal_gpio.h"
#include "hal_adc.h"
#include "hal_uart.h"
#include "hal_rcc.h"

#include "clock_init.h"
#include "pin_init.h"

/* ADC. */
#define BOARD_ADC_PORT        ADC
#define BOARD_ADC_IRQn        ADC_COMP_IRQn
#define BOARD_ADC_IRQHandler  ADC_COMP_IRQHandler
#define BOARD_ADC_CHN_NUM            1u     /* select the adc fixed channel 1. */
#define BOARD_ADC_SLOT_MASK          0x02   /* enable fixed channel 1. */
/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ


void BOARD_Init(void);
void BOARD_InitDebugConsole(void);

#endif /* __BOARD_INIT_H__ */
