/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Macros.
 */
#define BKP_REG_NUM 7u

/*
 * Variables.
 */

/*
 * Declerations.
 */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    /* Cancel write protection. */
    RCC_EnableBKPWriteProtect(false);

    uint8_t i = BKP_GetData(BOARD_DEBUG_BKP_PORT, BKP_REG_NUM);
    printf("reset cnt is: %d\r\n", i);
    i++;
    BKP_SetData(BOARD_DEBUG_BKP_PORT, BKP_REG_NUM, i);

    while (1)
    {
    }
}

/* EOF. */
