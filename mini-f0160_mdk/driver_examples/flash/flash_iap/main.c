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
 * Definitions.
 */

/*
 * Variables.
 */

uint8_t flash_data_buff[FLASH_PAGE_SIZE];

/*
 * Declerations.
 */
void flash_init(void);
void flash_erase_page(uint32_t addr);
void flash_read_page(uint32_t addr, uint8_t *buff);
void flash_program_page(uint32_t addr, uint8_t *buff);
void flash_print_page(uint8_t *buff);
/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("flash_iap example.\r\n");

    flash_init();

    while (1)
    {
        /* read data before the erase. */
        printf("\r\n read page ...\r\n");
        getchar();
        flash_read_page(BOARD_FLASH_PAGE_INDEX, flash_data_buff);
        flash_print_page(flash_data_buff);

        /* erase the page. */
        printf("\r\n erase page ...\r\n");
        getchar();
        flash_erase_page(BOARD_FLASH_PAGE_INDEX);
        printf("flash_erase_page() done.\r\n");

        /* read data after the erase. */
        printf("\r\n read page ...\r\n");
        getchar();
        flash_read_page(BOARD_FLASH_PAGE_INDEX, flash_data_buff);
        flash_print_page(flash_data_buff);

        /* program the page. */
        printf("\r\n program page ...\r\n");
        getchar();
        for (uint32_t i = 0u; i < FLASH_PAGE_SIZE; i++)
        {
            flash_data_buff[i] = i % 256u;
        }
        flash_program_page(BOARD_FLASH_PAGE_INDEX, flash_data_buff);
        printf("flash_program_page() done.\r\n");

        /* read the page after the program. */
        printf("\r\n read page ...\r\n");
        getchar();
        flash_read_page(BOARD_FLASH_PAGE_INDEX, flash_data_buff);
        flash_print_page(flash_data_buff);

        printf("\r\n done.\r\n");
        printf("press any key to retry the operations ...\r\n");
        getchar();
    }
}

void flash_init(void)
{
    FLASH_Unlock(BOARD_FLASH);
}

void flash_erase_page(uint32_t page)
{
    FLASH_SetCmd(BOARD_FLASH, FLASH_CMD_ERASE_PAGE);
    FLASH_SetAddr(BOARD_FLASH, BOARD_FLASH_BASE + page * FLASH_PAGE_SIZE);

    FLASH_SetCmd(BOARD_FLASH, FLASH_CMD_START_ERASE);

    while (! FLASH_WaitDone(BOARD_FLASH, 1000u) ); /* flash controller operation done. */
    while ( FLASH_STATUS_END_OF_OPERATION != FLASH_GetStatus(BOARD_FLASH) ); /* flash memory erase operation done. */
    FLASH_ClearStatus(BOARD_FLASH, FLASH_STATUS_END_OF_OPERATION);
}

void flash_read_page(uint32_t page, uint8_t *buff)
{
    uint32_t addr = BOARD_FLASH_BASE + page * FLASH_PAGE_SIZE;
    for (uint32_t i = 0u; i < FLASH_PAGE_SIZE; i++, buff++)
    {
        *buff = *((uint8_t *)(addr+i));
    }
}

void flash_program_page(uint32_t page, uint8_t *buff)
{
    uint32_t addr = BOARD_FLASH_BASE + page * FLASH_PAGE_SIZE;
    for (uint32_t i = 0u; i < FLASH_PAGE_SIZE; i+=2u, buff+=2u)
    {
        FLASH_SetCmd(BOARD_FLASH, FLASH_CMD_PROGRAM);
        FLASH_SetData16b(addr+i, *((uint16_t *)buff));
        while ( !FLASH_WaitDone(BOARD_FLASH, 100u) );
    }
}

void flash_print_page(uint8_t *buff)
{
    for (uint32_t i = 0u; i < FLASH_PAGE_SIZE; i++)
    {
        if ((i % 32u) == 0u)
        {
            printf("\r\n");
        }
        printf("%2x ", *(buff+i));
    }
    printf("\r\n");
}

/* EOF. */
