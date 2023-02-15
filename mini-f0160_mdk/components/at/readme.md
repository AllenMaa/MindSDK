# AT Server

[TOC]

# Introduction

Mainly realize the following functions

- Parse the received AT command and respond

- User can customize AT command set

   - Each AT command can realize four functions

     | Function | Expression | Description |
     | ---- | ---------- | -------------- |
     | Test function | AT+<x>=? | Used to query the parameter format and value range |
     | Query function | AT+<x>? | Used to return command parameters |
     | Setting function | AT+<x>=... | For user-defined parameters |
     | Execute function | AT+<x> | Used to perform related operations |

# Instructions for use

## Define AT adapter interface
Instantiate the **at_adapter_t** structure
```c
typedef struct{
    at_server_init_t init;          /* the at server initialization port. */
    at_server_write_t write;        /* the at adapter writer buffer port.*/
    at_server_read_t read;          /* the at adapter read buffer port. */
    char * buf;                     /* the at adapter receive buffer. */
    uint32_t buf_size;              /* the at adapter receive buffer size. */
}at_adapter_t;
```

## Define AT command set
Create an array of AT command set structures and instantiate the **at_cmd_t** structure
```c
typedef struct{
    char *name;                     /* the name of at command. */
    char *args_expr;                /* the parameter of at command. */
    at_server_test_t  test;         /* to query the command parameter format and value range. */
    at_server_query_t query;        /* to return the current value of the command parameter. */
    at_server_setup_t setup;        /* for user-defined parameter value. */
    at_server_exec_t  exec;         /* to execute related operations. */
}at_cmd_t;
```

## Initialize AT Server
The underlying interface are passed to the Server through the AT adapter. The corresponding APIs are **at_server_init()**。 And using the **at_server_set_cmd_list()** api to pass the at command list to the server.

## Start the AT Server task
Call the API **at_server_task()** to start the server and start working, waiting to receive commands and respond.
