/*!
* @file    rbuf.h
* @brief   This component implements a ring buffer component based on a array of static memory.
* @version 2.0
* @author  Andrew SU (suyong_yq@126.com)
* @date    2021-10
*/

#ifndef __RBUF_H__
#define __RBUF_H__

#include <stdint.h>
#include <stdbool.h>

/*!
* @brief Define structure for Ring Buffer's handler.
*
* The Ring Buffer is origanized as FIFO based on a array of static memory.
*/
typedef struct
{
    uint32_t buff_size; /*!< Keep the available count of byte in buffer's array */
    uint8_t *buff_mem;  /*!< Keep the first pointer to the buffer's array. This pointer is used to handler the memory. */
    uint32_t read_idx;  /*!< Keep the index of item in static array for FIFO's read pointer. */
    uint32_t write_idx; /*!< Keep the index of item in static array for FIFO's write pointer. */
    uint32_t count;     /*!< Record the current count of used item in the FIFO      .*/
} rbuf_handler_t;

/*!
* @brief Initialize the ring buffer.
*
* This function fills the allocated static memory into ring buffer's handle structure, and fills the
* read and write pointers with initial value.
*
* @param [out] handler Pointer to a empty ring buffer handle to be filled. See to #rbuf_handler_t.
* @param [in]  mem  Pointer to allocated static memory.
* @param [in]  size    Count of memory size in byte.
*/
void rbuf_init(rbuf_handler_t *handler, uint8_t *mem, uint32_t size);

/*!
* @brief Reset or Clean the ring buffer.
*
* This function clear all the items in the fifo. Actually, it just resets the write index, read
* index and the item count, then all the old data would be unavailable, while the new data would
* cover them.
*
* @param [in] handler Pointer to a ring buffer handle to be clean. See to #rbuf_handler_t.
*/
void rbuf_reset(rbuf_handler_t *handler);

/*!
* @brief Check if the buffer is empty.
*
* @param [in] handler Pointer to an available handler to be operated.
* @retval true  The buffer is empty.
* @retval false The buffer is not empty.
*/
bool rbuf_is_empty(rbuf_handler_t *handler);

/*!
* @brief Check if the buffer is full.
*
* @param [in] handler Pointer to an available handler to be operated.
* @retval true  The buffer is full.
* @retval false The buffer is not full.
*/
bool rbuf_is_full(rbuf_handler_t *handler);

/*!
* @brief Put data into buffer.
*
* @param [in] handler Pointer to an available handler to be operated.
* @param [in] dat The data to be put into buffer.
*/
void rbuf_input(rbuf_handler_t *handler, uint8_t dat);

/*!
* @brief Get out data from the buffer.
*
* @param [in] handler Pointer to an available handler to be operated.
* @retval The data from the buffer.
*/
uint8_t rbuf_output(rbuf_handler_t *handler);

#endif /* __RBUF_H__ */
