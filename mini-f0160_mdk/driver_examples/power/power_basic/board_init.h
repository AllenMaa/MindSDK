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
#include "hal_syscfg.h"
#include "hal_exti.h"
#include "hal_pwr.h"
#include "hal_power.h"

#include "clock_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ
#define BOARD_DEBUG_UART_FREQ_2M     2000000

/*SYSCFG*/
#define BOARD_SYSCFG_EXTIPORT        SYSCFG_EXTIPort_GPIOA
#define BOARD_SYSCFG_EXTILINE        SYSCFG_EXTILine_0

/*EXTI*/
#define BOARD_EXTI_PORT              EXTI
#define BOARD_EXTI_LINE              EXTI_LINE_0
#define BOARD_EXTI_IRQN              EXTI0_1_IRQn
#define BOARD_EXTI_IRQHandler        EXTI0_1_IRQHandler

/*POWER*/
#define BOARD_POWER_STANDBYWAKEUP_PORT      PWR_WAKEUP_PIN_1
#define BOARD_POWER_STANDBYWAKEUP_DELAY     PWR_StandbyWakeUpDelay_2

/*
 * Macros.
 */
#define MENU_MESSAGE "\r\nPress:\r\n\
\ta) for Run\r\n\
\tb) for Sleep\r\n\
\tc) for Stop\r\n\
\td) for DeepStop\r\n\
\te) for Standby\r\n\
-->Pull PA0 up to wake up the MCU from Sleep, Stop, DeepStop or Standby mode.\r\n\
Enter your input:\r\n"

void BOARD_Init(void);
void BOARD_InitDebugConsole(void);
void BOARD_ResetDebugConsole(uint32_t ClockFreq);
void BOARD_PowerModeSelect(uint8_t ch);

#endif /* __BOARD_INIT_H__ */

