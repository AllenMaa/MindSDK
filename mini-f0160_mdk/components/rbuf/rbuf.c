/* rbuf.c */
#include "rbuf.h"

void rbuf_init(rbuf_handler_t *handler, uint8_t *mem, uint32_t size)
{
    handler->buff_mem = mem;
    handler->buff_size = size;
    handler->read_idx = 0u;
    handler->write_idx = 0u;
    handler->count = 0u;
}

/* clean the fifo. */
void rbuf_reset(rbuf_handler_t *handler)
{
    handler->write_idx = 0u;
    handler->read_idx = 0u;
    handler->count = 0u;
}

//static uint32_t _RBUF32_NextIdx(uint32_t idx, uint32_t maxCnt)
//{
//    return ( ((idx+1U) == maxCnt) ? 0U : (idx+1U) );
//}

bool rbuf_is_empty(rbuf_handler_t *handler)
{
    //return (handler->read_idx == handler->write_idx);
    return (handler->count == 0u);
}

bool rbuf_is_full(rbuf_handler_t *handler)
{
    //return (  _RBUF32_NextIdx(handler->write_idx, handler->buff_size) == handler->read_idx);
    return (handler->count == handler->buff_size);
}

void rbuf_input(rbuf_handler_t *handler, uint8_t dat)
{
    *((handler->buff_mem)+(handler->write_idx)) = dat; /* 将数据保存在当前指针 */
    //handler->write_idx = _RBUF32_NextIdx(handler->write_idx, handler->buff_size);
    handler->write_idx = (handler->write_idx+1) % handler->buff_size;
    handler->count++;
}

uint8_t rbuf_output(rbuf_handler_t *handler)
{
    uint8_t dat = *((handler->buff_mem)+(handler->read_idx)); /* 从当前位置取数 */
    //handler->read_idx = _RBUF32_NextIdx(handler->read_idx, handler->buff_size);
    handler->read_idx = (handler->read_idx+1) % handler->buff_size;
    handler->count--;
    return dat;
}

/* EOF. */
