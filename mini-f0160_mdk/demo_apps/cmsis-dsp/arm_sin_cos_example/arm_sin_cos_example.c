/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "arm_math.h"
#include <math.h>
/*
 * Macros.
 */

#define MAX_BLOCKSIZE   32
#define DELTA           (0.0001f)

/*
 * Variables.
 */
/* Test input data for Floating point sin_cos example for 32-blockSize. */
const float32_t testInput_f32[MAX_BLOCKSIZE] =
{
   1.570796326794896619,  -1.244916875853235400,  -4.793533929171324800,   0.360705030233248850,   0.827929644170887320,  -3.299532218312426900,   3.427441903227623800,   3.422401784294607700,  
   0.941943896490312180,   0.502609575000365850,  -0.537345278736373500,   2.088817392965764500,  -1.693168684143455700,   6.283185307179590700,  -0.392545884746175080,   0.327893095115825040,
   3.070147440456292300,   0.170611405884662230,  -0.275275082396073010,  -2.395492805446796300,   0.847311163536506600,  -3.845517018083148800,   2.055818378415868300,   4.672594161978930800,
  -1.990923030266425800,   2.469305197656249500,   3.609002606064021000,  -4.586736582331667500,  -4.147080139136136300,   1.643756718868359500,  -1.150866392366494800,  -0.108308165334010680
};

const float32_t testRefOutput_f32 = 1.000000000;
/* */
uint32_t blockSize = 32;
float32_t  testOutput;
float32_t  cosOutput;
float32_t  sinOutput;
float32_t  cosSquareOutput;
float32_t  sinSquareOutput;

arm_status status;

/*
 * Declerations.
 */

/*
 * Functions.
 */
int main(void)
{
    uint8_t ch;
    float32_t diff;

    BOARD_Init();

    printf("cos & sin basic examples. \r\n");

    for(uint32_t i=0; i< blockSize; i++)
    {
        cosOutput = arm_cos_f32(testInput_f32[i]);
        printf("cosOutput = %f\r\n", cosOutput);
        sinOutput = arm_sin_f32(testInput_f32[i]);
        printf("sinOutput = %f\r\n", sinOutput);

        arm_mult_f32(&cosOutput, &cosOutput, &cosSquareOutput, 1);
        arm_mult_f32(&sinOutput, &sinOutput, &sinSquareOutput, 1);

        arm_add_f32(&cosSquareOutput, &sinSquareOutput, &testOutput, 1);

        /* absolute value of difference between ref and test */
        diff = fabsf(testRefOutput_f32 - testOutput);
        printf("diff = %f\r\n", diff);

        /* Comparison of sin_cos value with reference */
        status = (diff > DELTA) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;

        if ( status == ARM_MATH_TEST_FAILURE)
        {
           break;
        }
    }
    if (status != ARM_MATH_SUCCESS)
    {
        printf("FAILURE\r\n");
    }
    else
    {
        printf("SUCCESS\r\n");
    }
    while (1)
    {
        ch = getchar();
        putchar(ch);
    }
}

/* EOF. */

