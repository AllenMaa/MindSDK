/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "softi2c.h"

/*
* hal bonding level api.
*/
static void softi2c_hal_delay(softi2c_obj_t *self)
{
    softi2c_if_t *i2c_if = (softi2c_if_t *)self->i2c_if;

    i2c_if->delay(self->bps_delay);
}

static int softi2c_hal_scl_rel(softi2c_obj_t *self)
{
    softi2c_if_t *i2c_if = (softi2c_if_t *)self->i2c_if;

    i2c_if->scl_rel(); /* gpio input mode. */
    softi2c_hal_delay(self);

    /* wait for the scl pin released by remote device or timeout. */
    uint32_t timeout = self->timeout_delay;
    for (; i2c_if->scl_read() == 0 && timeout; --timeout)
    {
        i2c_if->delay(1);
    }

    if (timeout == 0)
    {
        return -1; /* timeout. */
    }
    return 0;
}

static void softi2c_hal_scl_low(softi2c_obj_t *self)
{
    softi2c_if_t *i2c_if = (softi2c_if_t *)self->i2c_if;

    i2c_if->scl_low();
}

static void softi2c_hal_sda_rel(softi2c_obj_t *self)
{
    softi2c_if_t *i2c_if = (softi2c_if_t *)self->i2c_if;

    i2c_if->sda_rel();
}

static void softi2c_hal_sda_low(softi2c_obj_t *self)
{
    softi2c_if_t *i2c_if = (softi2c_if_t *)self->i2c_if;

    i2c_if->sda_low();
}

static int softi2c_hal_sda_read(softi2c_obj_t *self)
{
    softi2c_if_t *i2c_if = (softi2c_if_t *)self->i2c_if;

    return i2c_if->sda_read();
}

/*
 * functional api.
 */

static int softi2c_start(softi2c_obj_t *self)
{
    softi2c_hal_sda_rel(self);
    softi2c_hal_delay(self);
    int ret = softi2c_hal_scl_rel(self);
    if (ret != 0)
    {
        return ret; /* timeout by locked. */
    }
    softi2c_hal_sda_low(self);
    softi2c_hal_delay(self);
    return 0; /* succ. */
}

static int softi2c_stop(softi2c_obj_t *self)
{
    softi2c_hal_delay(self);
    softi2c_hal_sda_low(self);
    softi2c_hal_delay(self);
    int ret = softi2c_hal_scl_rel(self);
    softi2c_hal_sda_rel(self);
    softi2c_hal_delay(self);
    return ret;
}

/*
 * return value:
 *     0 - byte written and ack received.
 *     1 - byte written and nack received.
 *    <0 - error, with errno being the negative of the return value.
 */
static int softi2c_write_byte(softi2c_obj_t *self, uint8_t val)
{
    softi2c_hal_delay(self);
    softi2c_hal_scl_low(self);

    for (int i = 7; i >= 0; i--)
    {
        if ((val >> i) & 1)
        {
            softi2c_hal_sda_rel(self);
        }
        else
        {
            softi2c_hal_sda_low(self);
        }
        softi2c_hal_delay(self);
        int ret = softi2c_hal_scl_rel(self);
        if (ret != 0)
        {
            softi2c_hal_sda_rel(self);
            return ret; /* timeout. */
        }
        softi2c_hal_scl_low(self);
    }

    softi2c_hal_sda_rel(self);
    softi2c_hal_delay(self);
    int ret = softi2c_hal_scl_rel(self);
    if (ret != 0)
    {
        return ret; /* timeout. */
    }

    int ack = softi2c_hal_sda_read(self);
    softi2c_hal_delay(self);
    softi2c_hal_scl_low(self);

    return ack;
}

/*
 * return value:
 *    0 - success.
 *   <0 - error, with errno being the negative of the return value.
 */
static int softi2c_read_byte(softi2c_obj_t *self, uint8_t *val, int nack)
{
    softi2c_hal_delay(self);
    softi2c_hal_scl_low(self);
    softi2c_hal_delay(self);

    uint8_t data = 0;
    for (int i = 7; i >= 0; i--)
    {
        int ret = softi2c_hal_scl_rel(self);
        if (ret != 0)
        {
            return ret;
        }
        data = (data << 1) | softi2c_hal_sda_read(self);
        softi2c_hal_scl_low(self);
        softi2c_hal_delay(self);
    }
    *val = data;

    /* send ack/nack bit. */
    if (nack)
    {
        softi2c_hal_sda_low(self);
    }
    softi2c_hal_delay(self);
    int ret = softi2c_hal_scl_rel(self);
    if (ret != 0)
    {
        softi2c_hal_sda_rel(self);
        return ret;
    }
    softi2c_hal_scl_low(self);
    softi2c_hal_sda_rel(self);

    return 0; /* success. */
}

static int softi2c_transfer_single(softi2c_obj_t *self, uint16_t addr, uint8_t *buf, uint32_t len, uint32_t flags)
{
    /* start the i2c transaction. */
    int ret = softi2c_start(self); /* ret=0 ok. */
    if (ret != 0)
    {
        return ret; /* start error. */
    }

    /* write the slave addr. */
    ret = softi2c_write_byte(self, (addr << 1) | (flags & SOFTI2C_FLAG_READ) ); /* ret = 0, ok. */
    if (ret < 0)
    {
        return ret; /* bus error. */
    }
    else if (ret != 0)
    {
        /* nack received, release the bus clean. */
        softi2c_stop(self);
        return -1; /* nack, no target device. */
    } /* ret = 0, ok. */

    if (flags & SOFTI2C_FLAG_READ) /* read. */
    {
        while (len--)
        {
            ret = softi2c_read_byte(self, buf++, len); /* ret = 0, ok. */
            if (ret != 0)
            {
                return ret;
            }
        }
    }
    else /* write. */
    {
        while (len--)
        {
            ret = softi2c_write_byte(self, *buf++);
            if (ret < 0)
            {
                return ret;
            }
            else if (ret != 0) /* ret= 0, ok. */
            {
                /* nack received, send stop. */
                break;
            }
        }
    }

    /* finish a i2c trans. */
    if (flags & SOFTI2C_FLAG_STOP)
    {
        ret = softi2c_stop(self); /* ret= 0, ok. */
        if (ret != 0)
        {
            return ret; /* timeout. */
        }
    }

    return 0; /* succ. */
}

void softi2c_init(softi2c_obj_t *self, softi2c_if_t *i2c_if, uint32_t bps_delay, uint32_t timeout_delay)
{
    self->i2c_if = i2c_if;
    self->bps_delay = bps_delay;
    self->timeout_delay = timeout_delay;

    i2c_if->init();
    softi2c_stop(self);
}

int softi2c_read(softi2c_obj_t *self, uint16_t addr, uint8_t *rxbuf, uint32_t len, bool stop)
{
    uint32_t flags = SOFTI2C_FLAG_READ | (stop ? SOFTI2C_FLAG_STOP : 0u);
    return softi2c_transfer_single(self, addr, rxbuf, len, flags);
}

int softi2c_write(softi2c_obj_t *self, uint16_t addr, uint8_t *txbuf, uint32_t len, bool stop)
{
    uint32_t flags = stop ? SOFTI2C_FLAG_STOP : 0u;
    return softi2c_transfer_single(self, addr, txbuf, len, flags);
}

int softi2c_scan(softi2c_obj_t *self, uint16_t *addrs, uint32_t len)
{
    int ret = 0;
    for (uint16_t addr = 0x00; addr < 0x80; ++addr)
    {
        if (softi2c_write(self, addr, NULL, 0, true) == 0)
        {
            *addrs = addr;
            addrs++;
            ret++; /* count the available addrs. */
            if (ret >= len)
            {
                break;
            }
        }
    }

    return ret;
}

/* EOF. */
