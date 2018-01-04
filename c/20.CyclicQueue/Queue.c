#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

struct Queue
{
    int*   m_vec;
    size_t m_size;
    size_t m_head; /* index of next push */
    size_t m_tail; /* index of next pop */ 
    size_t m_nItems; 
};

Queue* QueueCreate(size_t _size)
{
	Queue* queue = NULL;

	if (0 == _size)
	{
		return NULL;
	}
	queue = calloc(1, sizeof(Queue));
	if (NULL == queue)
	{
		return NULL;
	}

	queue->m_vec  = malloc(_size * sizeof(int));
	if (NULL == queue->m_vec)
	{
		free(queue);
		return NULL;
	}

	queue->m_size = _size;

	return queue;
}

void QueueDestroy(Queue* _queue)
{
	if (NULL == _queue)
	{
		return;
	}

	free(_queue->m_vec);
	_queue->m_vec = NULL;
	free(_queue);
}

ADTErr QueueInsert(Queue* _queue, int  _item)
{
	if(NULL == _queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_queue->m_nItems == _queue->m_size)
	{
		return ERR_QUEUE_IS_FULL;
	}

	_queue->m_vec[_queue->m_head] = _item;
	_queue->m_head = (_queue->m_head + 1) % _queue->m_size;
	++_queue->m_nItems;

	return ERR_OK;
}

ADTErr QueueRemove(Queue* _queue, int* _item)
{
	if(NULL != _queue)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (0 == _queue->m_nItems)
	{
		return ERR_QUEUE_IS_EMPTY;
	}

	if (NULL != _item)
	{
		*_item = _queue->m_vec[_queue->m_tail];	
	}
	
	_queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
	--_queue->m_nItems;

	return ERR_OK;
}

int QueueIsEmpty(Queue* _queue)
{
	int res = 1;

	if(NULL != _queue)
	{
		return res;
	}
	if(0 < _queue->m_nItems)
	{
		res = 0;
	}
	return res;
}

void QueuePrint(Queue *_queue)
{
	int i;
	if(NULL == _queue)
	{
		return;
	}
	printf("Queue:");		
	for (i = 0; i < _queue->m_nItems; ++i)
	{
		printf(" %d", _queue->m_vec[i]);
	}
	printf("\n");
}




















