/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>

#include "board_init.h"
#include "hal_hwdiv.h"

/*
 * Definitions.
 */

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
    uint32_t a,b;

    BOARD_Init();

    HWDIV_EnableUsignBit(HWDIV,true);
    HWDIV_EnableInterrupt(HWDIV,false);


    printf("\r\nhwdiv_basic example.\r\n");

    a = HWDIV_CalcUsign(HWDIV,12,0);
    b = HWDIV_GetRMDRBitsUsign(HWDIV);

    if( HWDIV_GetOVFBit(HWDIV) )
    {
        HWDIV_ClearOVFBit(HWDIV);
    }

    printf("\r\nquotient = %u, remainder = %u\r\n", (unsigned)a, (unsigned)b);

    a = HWDIV_CalcUsign(HWDIV,12,6);
    b = HWDIV_GetRMDRBitsUsign(HWDIV);

    printf("\r\nquotient = %u, remainder = %u\r\n", (unsigned)a, (unsigned)b);

    a = HWDIV_CalcUsign(HWDIV,22,5);
    b = HWDIV_GetRMDRBitsUsign(HWDIV);

    printf("\r\nquotient = %u, remainder = %u\r\n", (unsigned)a, (unsigned)b);

    while (1)
    {
    }
}

/* EOF. */
