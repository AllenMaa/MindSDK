/* softi2c.h */
#ifndef __SOFTI2C_H__
#define __SOFTI2C_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define SOFTI2C_FLAG_READ  (1u << 0u)
#define SOFTI2C_FLAG_STOP  (1u << 1u)

typedef struct
{
    /* setup pins and timer. */
    void (*init)(void);

    /* sda pin. */
    void (*sda_low)(void);
    void (*sda_rel)(void);
    int  (*scl_read)(void);

    /* scl pin. */
    void (*scl_low)(void);
    void (*scl_rel)(void);
    int  (*sda_read)(void);

    /* timer. */
    void (*delay)(uint32_t ticks);
} softi2c_if_t;

typedef struct
{
    softi2c_if_t *i2c_if;
    uint32_t bps_delay; /* delay ticks for baudrate. */
    uint32_t timeout_delay; /* delay ticks for scl pin timeout. */
} softi2c_obj_t;

void softi2c_init (softi2c_obj_t *self, softi2c_if_t *i2c_if, uint32_t bps_delay, uint32_t timeout_delay);
int  softi2c_read (softi2c_obj_t *self, uint16_t addr, uint8_t *rxbuf, uint32_t len, bool stop);
int  softi2c_write(softi2c_obj_t *self, uint16_t addr, uint8_t *txbuf, uint32_t len, bool stop);
int  softi2c_scan (softi2c_obj_t *self, uint16_t *addrs, uint32_t len);

#endif /* __SOFTI2C_H__ */
