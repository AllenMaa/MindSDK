/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "string.h"
#include "core_json.h"

/*
 * Macros.
 */

#define JSON_BUF_SIZE 20

/*
 * Variables.
 */
 
/* json raw. */
const char str_json[] =
"{\r\n"
"    \"string\":\"MindMotion\",\r\n"
"    \"number\":123,\r\n"
"    \"array\":[1,2,\"123\",{\"string\":\"123456\"}],\r\n"
"    \"sub_json\":{\"string\":\"654321\"}\r\n"
"}";

/* query list. */
const char json_query_list[][JSON_BUF_SIZE] = 
{
    "string",
    "number",
    "array",
    "sub_json",
};

/*
 * Declerations.
 */

/* check if json raw is valid. */
void app_json_check(const char * str);

/* get the value of query. */
void app_json_query(const char * str);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("core_json basic demo.\r\n");

    /* print json raw. */
    printf("%s\r\n", str_json);

    /* check. */
    app_json_check(str_json);

    /* query. */
    app_json_query(str_json);

    while (1)
    {
    }
}

/* check if json raw is valid. */
void app_json_check(const char * str)
{
    /* check. */
    JSONStatus_t status = JSON_Validate(str, strlen(str) );

    if (JSONSuccess == status)
    {
        printf("the json raw is valid.\r\n");
    }
    else
    {
        printf("the json raw is invalid.\r\n");
    }
}

/* get the value of query. */
void app_json_query(const char * str)
{
    char * out_value;
    size_t out_len;

    for (uint32_t i = 0u; i < sizeof(json_query_list) / JSON_BUF_SIZE; i++)
    {
        if (JSONSuccess == (JSON_Search( (char*)str, strlen(str), json_query_list[i], strlen(json_query_list[i]), &out_value, &out_len) ) )
        {
            printf("the %s value is %.*s\r\n", json_query_list[i], out_len, out_value);
        }
        else
        {
            printf("the %s value not found.", json_query_list[i]);
        }
    }
}

/* EOF. */

