#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__


#include <stddef.h>  /* size_t */


typedef enum
{
	QUEUE_OK	=0,
	QUEUE_NOT_INITIALIZED,
	QUEUE_ALLOCATION_FAILED
	} ProtectedQueueResult;

typedef struct ProtectedQueue ProtectedQueue;

ProtectedQueue* ProtectedQueueCreate(size_t _size);

void ProtectedQueueDestroy(ProtectedQueue* _queue);

ProtectedQueueResult ProtectedQueueInsert(ProtectedQueue* _queue, void* _item);

ProtectedQueueResult ProtectedQueueRemove(ProtectedQueue* _queue, void** _item);

int ProtectedQueueIsEmpty(ProtectedQueue* _queue);


#endif /* #ifndef __PROTECTED_QUEUE_H__ */



