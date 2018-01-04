#ifndef __ADTERR_H__
#define __ADTERR_H__

typedef enum
{
    ERR_OK              =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_LIST_IS_EMPTY,
    ERR_STACK_BBBBB = 30

} ADTErr;

#endif /* #ifndef __ADTERR_H__ */

