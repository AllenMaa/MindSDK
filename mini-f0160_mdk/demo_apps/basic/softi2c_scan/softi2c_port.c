/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "softi2c.h"
#include "hal_gpio.h"
#include "board_init.h"

static void brd_softi2c_init(void);
static void brd_softi2c_sda_low(void);
static void brd_softi2c_sda_rel(void);
static int  brd_softi2c_sda_read(void);
static void brd_softi2c_scl_low(void);
static void brd_softi2c_scl_rel(void);
static int  brd_softi2c_scl_read(void);
static void brd_softi2c_delay(uint32_t ticks);

/* the softi2c interface. */
const softi2c_if_t brd_softi2c_if =
{
    .init    = brd_softi2c_init,
    .sda_low = brd_softi2c_sda_low,
    .sda_rel = brd_softi2c_sda_rel,
    .sda_read= brd_softi2c_sda_read,
    .scl_low = brd_softi2c_scl_low,
    .scl_rel = brd_softi2c_scl_rel,
    .scl_read= brd_softi2c_scl_read,
    .delay   = brd_softi2c_delay,
};

/* init hardware. */
static void brd_softi2c_init(void)
{
    GPIO_Init_Type gpio_init;

    /* config the i2c scl pin is release status (in floating). */
    gpio_init.Pins    = BOARD_SOFTI2C_SCL_GPIO_PIN;
    gpio_init.PinMode = GPIO_PinMode_In_Floating,
    gpio_init.Speed   = GPIO_Speed_50MHz,
    gpio_init.Pins    = BOARD_SOFTI2C_SDA_GPIO_PIN,
    GPIO_Init(BOARD_SOFTI2C_SCL_GPIO_PORT, &gpio_init);
    GPIO_PinAFConf(BOARD_SOFTI2C_SCL_GPIO_PORT, gpio_init.Pins, GPIO_AF_15);

    /* config the i2c sda pin is release status (in floating). */
    gpio_init.Pins    = BOARD_SOFTI2C_SDA_GPIO_PIN;
    gpio_init.PinMode = GPIO_PinMode_In_Floating,
    gpio_init.Speed   = GPIO_Speed_50MHz,
    gpio_init.Pins    = BOARD_SOFTI2C_SDA_GPIO_PIN,
    GPIO_Init(BOARD_SOFTI2C_SDA_GPIO_PORT, &gpio_init);
    GPIO_PinAFConf(BOARD_SOFTI2C_SCL_GPIO_PORT, gpio_init.Pins, GPIO_AF_15);

    /* pre config the scl & sda pin level when init pins out_push_pull. */
    GPIO_WriteBit(BOARD_SOFTI2C_SCL_GPIO_PORT, BOARD_SOFTI2C_SCL_GPIO_PIN, 0u);
    GPIO_WriteBit(BOARD_SOFTI2C_SDA_GPIO_PORT, BOARD_SOFTI2C_SDA_GPIO_PIN, 0u);
}

/* sda low level, out_push_pull, pull down i2c sda. */
static void brd_softi2c_sda_low(void)
{
    GPIO_Init_Type gpio_init = {
        .PinMode = GPIO_PinMode_Out_PushPull,
        .Speed   = GPIO_Speed_50MHz,
        .Pins    = BOARD_SOFTI2C_SDA_GPIO_PIN,
    };
    GPIO_Init(BOARD_SOFTI2C_SDA_GPIO_PORT, &gpio_init);
}

/* sda high level, in_floating, release i2c sda. */
static void brd_softi2c_sda_rel(void)
{
    GPIO_Init_Type gpio_init = {
        .PinMode = GPIO_PinMode_In_Floating,
        .Speed   = GPIO_Speed_50MHz,
        .Pins    = BOARD_SOFTI2C_SDA_GPIO_PIN,
    };
    GPIO_Init(BOARD_SOFTI2C_SDA_GPIO_PORT, &gpio_init);
}

/* read i2c sda status. */
static int brd_softi2c_sda_read(void)
{
    if (GPIO_ReadInDataBit(BOARD_SOFTI2C_SDA_GPIO_PORT, BOARD_SOFTI2C_SDA_GPIO_PIN) )
    {
        return 1; /* high level. */
    }
    else
    {
        return 0; /* low level. */
    }
}

/* scl low level, out_push_pull, pull down i2c scl. */
static void brd_softi2c_scl_low(void)
{
    GPIO_Init_Type gpio_init = {
        .PinMode = GPIO_PinMode_Out_PushPull,
        .Speed   = GPIO_Speed_50MHz,
        .Pins    = BOARD_SOFTI2C_SCL_GPIO_PIN,
    };
    GPIO_Init(BOARD_SOFTI2C_SCL_GPIO_PORT, &gpio_init);
}

/* scl high level, in_floating, release i2c scl. */
static void brd_softi2c_scl_rel(void)
{
    GPIO_Init_Type gpio_init = {
        .PinMode = GPIO_PinMode_In_Floating,
        .Speed   = GPIO_Speed_50MHz,
        .Pins    = BOARD_SOFTI2C_SCL_GPIO_PIN,
    };
    GPIO_Init(BOARD_SOFTI2C_SCL_GPIO_PORT, &gpio_init);
}

/* read i2c scl status. */
static int brd_softi2c_scl_read(void)
{
    if (GPIO_ReadInDataBit(BOARD_SOFTI2C_SCL_GPIO_PORT, BOARD_SOFTI2C_SCL_GPIO_PIN) )
    {
        return 1; /* high level. */
    }
    else
    {
        return 0; /* low level. */
    }
}

/* soft delay. */
static void brd_softi2c_delay(uint32_t ticks)
{
    for (uint32_t i = 0; i < ticks; i++)
    {
        __NOP();
    }
}

/* EOF. */
