#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__


#include <stddef.h>  /* size_t */


typedef struct ProtectedQueue ProtectedQueue;

typedef enum
{
	QUEUE_OK	=0,
	QUEUE_NOT_INITIALIZED_ERROR,
	QUEUE_INV_ARG_ERROR,
	QUEUE_ALLOCATION_FAILED_ERROR
} ProtectedQueueResult;


ProtectedQueue* ProtectedQueueCreate(size_t _size);

void ProtectedQueueDestroy(ProtectedQueue* _queue);

ProtectedQueueResult ProtectedQueueInsert(ProtectedQueue* _queue, void* _item);

ProtectedQueueResult ProtectedQueueRemove(ProtectedQueue* _queue, void** _item);

int ProtectedQueueIsEmpty(ProtectedQueue* _queue);


#endif /* #ifndef __PROTECTED_QUEUE_H__ */



