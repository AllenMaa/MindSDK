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
#define APP_CRC_BUFLEN 3u

/*
 * Variables.
 */
uint8_t app_crc_in_buf[APP_CRC_BUFLEN] = {0x11,0x22,0x33};

/*
 * Declerations.
 */
void app_crc_init();
uint32_t app_crc_software_crc32(uint8_t *buf, int len);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    app_crc_init();
    printf("crc_basic example.\r\n");

    for (uint8_t i = 0u; i < APP_CRC_BUFLEN; i++)
    {
        CRC_SetData(BOARD_CRC_PORT, app_crc_in_buf[i]);
    }
    uint32_t app_crc_hareware_result = CRC_GetResult(BOARD_CRC_PORT);
    uint32_t app_crc_software_result = app_crc_software_crc32(app_crc_in_buf, APP_CRC_BUFLEN);

    if (app_crc_hareware_result == app_crc_software_result)
    {
        printf("matched.\r\n");
        printf("hardware crc: %x\r\n", (unsigned int)(long)app_crc_hareware_result);
        printf("software crc: %x\r\n", (unsigned int)(long)app_crc_software_result);
    }
    else
    {
        printf("mismatched.\r\n");
        printf("hardware crc: %x\r\n", (unsigned int)(long)app_crc_hareware_result);
        printf("software crc: %x\r\n", (unsigned int)(long)app_crc_software_result);
    }

    while (1)
    {
    }
}

/* CRC initialization. */
void app_crc_init()
{
    CRC_Init_Type crc_init;
    crc_init.Algorithm = CRC_Algorithm_CRC32;
    crc_init.InEndian  = CRC_DataEndian_LittleEndian;
    crc_init.OutEndian = CRC_DataEndian_LittleEndian;
    crc_init.Width     = CRC_Width_8b;

    CRC_Init(BOARD_CRC_PORT, &crc_init);
}

/* CRC software caculate, use CRC-32 algorithm. */
uint32_t app_crc_software_crc32(uint8_t *buf, int len)
{
    uint32_t crc = 0xFFFFFFFF;
    uint32_t mask;

    for (int i = 0; i < len; i++)
    {
        crc = crc ^ (uint32_t)buf[i];
        for (int j = 7; j >= 0; j--)
        {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
    }
    return ~crc;
}

/* EOF. */

