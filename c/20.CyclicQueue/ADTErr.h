#ifndef __ADTERR_H__
#define __ADTERR_H__

typedef enum
{
    ERR_OK              =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_QUEUE_IS_FULL,
    ERR_QUEUE_IS_EMPTY,
    /* Vector Errors */
    /* Stack  Errors */
    ERR_STACK_BBBBB = 30
    /* LinkedList  Errors */
    /* Bit Vector*/
} ADTErr;

#endif /* #ifndef __ADTERR_H__ */
