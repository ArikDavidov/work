#ifndef __ADTERR_H__
#define __ADTERR_H__

typedef enum
{
    ERR_OK              =0,
    ERR_NOT_INITIALIZED,
    ERR_ILLEGAL_INPUT,
    ERR_VALUE_ALREADY_EXISTS,
	ERR_VALUE_NOT_FOUND,
    ERR_HASH_IS_FULL
} ADTErr;

#endif /* #ifndef __ADTERR_H__ */
