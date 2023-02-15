/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Macros.
 */

#define APP_I3C_STATIC_ADDR     0x30 /* i3c static addr. */
#define APP_XFER_BUF_LEN        16   /* the buffer size of queue. */

/*
 * Variables.
 */

uint8_t app_xfer_buf[APP_XFER_BUF_LEN] = {0}; /* the buffer of queue that stash rx data. */
uint8_t app_xfer_push = 0; /* queue push head. */
uint8_t app_xfer_pop  = 0; /* queue pop head. */
uint8_t app_xfer_cnt  = 0; /* queue length. */

/*
 * Declerations.
 */

void app_i3c_init(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("i3c_slave_basic example.\r\n");

    app_i3c_init(); /* init i3c. */

    while (1)
    {
        /* wait target matched. */
        I3C_ClearStatus(BOARD_I3C_PORT, I3C_STATUS_ADDR_MATCHED); /* clear addr matched status. */
        while(0 == (I3C_GetStatus(BOARD_I3C_PORT) & I3C_STATUS_ADDR_MATCHED)) /* wait addr matched. */
        {}

        /* wait bus stop. */
        I3C_ClearStatus(BOARD_I3C_PORT, I3C_STATUS_BUS_STOP); /* clear stop status. */
        while(0 == (I3C_GetStatus(BOARD_I3C_PORT) & I3C_STATUS_BUS_STOP)) /* xfer data until received stop signal. */
        {
            /* recv data. */
            if (I3C_GetStatus(BOARD_I3C_PORT) & I3C_STATUS_RX_NOT_EMPTY) /* read data if rx fifo not empty. */
            {
                app_xfer_buf[app_xfer_push] = I3C_GetData(BOARD_I3C_PORT); /* queue push. */
                app_xfer_push++; /* push head inc. */
                app_xfer_push %= sizeof(app_xfer_buf);
                app_xfer_cnt++; /* queue len inc. */
            }

            /* send data. */
            if (I3C_GetStatus(BOARD_I3C_PORT) & I3C_STATUS_TX_NOT_FULL && app_xfer_cnt > 0) /* write data if xfer_buf has data & tx fifo not full. */
            {
                app_xfer_cnt--; /* queue len dec. */
                I3C_PutData(BOARD_I3C_PORT, app_xfer_buf[app_xfer_pop], false); /* queue pop. */
                app_xfer_pop++; /* pop head inc. */
                app_xfer_pop %= sizeof(app_xfer_buf);
            }
        }

        printf("xfer done.\r\n");
    }
}

/* init i3c. */
void app_i3c_init(void)
{
    I3C_Slave_Init_Type i3c_init;
    i3c_init.ClockFreqHz = BOARD_I3C_FREQ;
    i3c_init.StaticAddr  = APP_I3C_STATIC_ADDR;
    I3C_InitSlave(BOARD_I3C_PORT, &i3c_init);

    /* enable i3c. */
    I3C_Enable(BOARD_I3C_PORT, true);
}

/* EOF. */
