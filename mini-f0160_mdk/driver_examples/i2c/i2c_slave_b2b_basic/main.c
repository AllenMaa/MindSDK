/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"

/*
 * Macros.
 */
#define APP_I2C_SLAVE_ADDR  0x30  /* I2C target device address. */
#define APP_I2C_BUF_LEN     16u     /* The size of I2C slave buf write and read array. */

/*
 * Variables.
 */
static uint32_t app_i2c_xfer_buf[APP_I2C_BUF_LEN];  /* I2C slave buf. */
volatile uint32_t app_i2c_txidx = 0u;  /* Index of i2c slave tx data. */
volatile uint32_t app_i2c_rxidx = 0u; /* Index of i2c slave rx data. */
I2C_Slave_Init_Type  i2c_init;
I2C_SlaveXfer_Type  i2c_xfer;

/*
 * Declerations.
 */
void app_i2c_init(void);
void app_i2c_xfer(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\ni2c_slave_b2b_basic example\r\n");

    /* Initialize I2C. */
    app_i2c_init();

    while (1)
    {
        app_i2c_xfer();
    }
}

/* Initialize I2C */
void app_i2c_init(void)
{
    /* Setup I2C initialization values. */
    i2c_init.SlaveAddr = APP_I2C_SLAVE_ADDR;
    i2c_xfer.BufLen = APP_I2C_BUF_LEN;
    i2c_xfer.RxIdx = app_i2c_rxidx;
    i2c_xfer.TxIdx = app_i2c_txidx;
    i2c_xfer.XferBuf = app_i2c_xfer_buf;

    /* Initialize I2C master. */
    I2C_InitSlave(BOARD_I2C_PORT, &i2c_init);

    /* Enable I2C. */
    I2C_Enable(BOARD_I2C_PORT, true);
}

/* I2C slave xfer. */
void app_i2c_xfer(void)
{
    I2C_SlaveReadData(BOARD_I2C_PORT, &i2c_xfer);
    I2C_SlaveWriteData(BOARD_I2C_PORT, &i2c_xfer);
}

/* EOF. */

