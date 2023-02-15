/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "softi2c.h"

/*
 * Macros.
 */

/* the size of app_addr_buf[]. */
#define APP_ADDR_BUF_SIZE 128u

/*
 * Variables.
 */

/* softi2c interface. */
extern const softi2c_if_t brd_softi2c_if;

/* softi2c object. */
static softi2c_obj_t app_softi2c_obj;

/* the buf to save scanned addr. */
uint16_t app_addr_buf[APP_ADDR_BUF_SIZE];

/*
 * Declerations.
 */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("softi2c_scan demo.\r\n");

    /* init soft i2c. */
    softi2c_init(&app_softi2c_obj, (softi2c_if_t*)&brd_softi2c_if, BOARD_SOFTI2C_BPSDELAY, BOARD_SOFTI2C_TIMEOUT_DELAY);

    printf("press any key to scan i2c bus.\r\n");

    while (1)
    {
        getchar();

        /* scan the i2c bus. */
        int num = softi2c_scan(&app_softi2c_obj, app_addr_buf, APP_ADDR_BUF_SIZE);

        /* print scanned i2c addr. */
        for(uint32_t i = 0; i < num; i++)
        {
            printf("0x%02X addr scanned.\r\n", app_addr_buf[i]);
        }
    }
}

/* EOF. */
