#include "ProtectedQueue.h"

#include <stdlib.h>
#include <pthread.h>		/* pthread_mutex_init, pthread_mutex_destroy */
#include <semaphore.h>


struct ProtectedQueue
{
	/* TODO magic */
	void**			m_items;
	size_t			m_size;
	size_t			m_head;				/* index of next insert */
	size_t			m_tail;				/* index of next remove */
	size_t			m_nItems;
	pthread_cond_t	m_canInsert;
	pthread_cond_t	m_canRemove;
	pthread_mutex_t	m_mutex;
};


ProtectedQueue* ProtectedQueueCreate(size_t _size)
{
	ProtectedQueue* queue = NULL;
	
	if (0 == _size)
	{
		return NULL;
	}
	
	queue = malloc(sizeof(ProtectedQueue));
	if (!queue)
	{
		return NULL;
	}

	queue->m_items = malloc(_size * sizeof(void*));
	if (NULL == queue->m_items)
	{
		free(queue);
		return NULL;
	}

	queue->m_size = _size;
	queue->m_head = 0;
	queue->m_tail = 0;
	queue->m_nItems = 0;
	pthread_cond_init(&queue->m_canInsert, NULL);
	pthread_cond_init(&queue->m_canRemove, NULL);
	pthread_mutex_init(&queue->m_mutex, NULL);

	return queue;
}

void ProtectedQueueDestroy(ProtectedQueue* _queue)
{
	if (!_queue)
	{
		return;
	}

	pthread_mutex_destroy(&_queue->m_mutex);
	pthread_cond_destroy(&_queue->m_canRemove);
	pthread_cond_destroy(&_queue->m_canInsert);

	free(_queue->m_items);
	_queue->m_items = NULL;
	free(_queue);
}

ProtectedQueueResult ProtectedQueueInsert(ProtectedQueue* _queue, void* _item)
{
	if(!_queue)
	{
		return QUEUE_NOT_INITIALIZED_ERROR;
	}
	
	pthread_mutex_lock(&_queue->m_mutex);
	while (_queue->m_nItems == _queue->m_size)
	{
		pthread_cond_wait(&_queue->m_canInsert, &_queue->m_mutex);
	}

	_queue->m_items[_queue->m_head] = _item;
	_queue->m_head = (_queue->m_head + 1) % _queue->m_size;
	++_queue->m_nItems;

	pthread_mutex_unlock(&_queue->m_mutex);
	pthread_cond_signal(&_queue->m_canRemove);

	return QUEUE_OK;
}

ProtectedQueueResult ProtectedQueueRemove(ProtectedQueue* _queue, void** _item)
{
	if(!_queue)
	{
		return QUEUE_NOT_INITIALIZED_ERROR;
	}
	if(!_item)
	{
		return QUEUE_INV_ARG_ERROR;
	}
	
	pthread_mutex_lock(&_queue->m_mutex);
	while (0 == _queue->m_nItems)
	{
		pthread_cond_wait(&_queue->m_canRemove, &_queue->m_mutex);
	}

	*_item = _queue->m_items[_queue->m_tail];
	_queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
	--_queue->m_nItems;	
	
	pthread_mutex_unlock(&_queue->m_mutex);
	pthread_cond_signal(&_queue->m_canInsert);	
	
	return QUEUE_OK;
}

int ProtectedQueueIsEmpty(ProtectedQueue* _queue)
{
	return (!_queue || 0 == _queue->m_nItems) ? 1 : 0;
}

















