#include "ProtectedQueue.h"

#include <stdlib.h>
#include <pthread.h>		/* pthread_mutex_init, pthread_mutex_destroy */
#include <semaphore.h>


struct ProtectedQueue
{
	/* TODO magic */
	void**	m_items;
	size_t	m_size;
	size_t	m_head;				/* index of next insert */
	size_t	m_tail;				/* index of next remove */ 
	sem_t	m_empty;
	sem_t	m_full;
	pthread_mutex_t m_mutex;
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

	queue->m_items  = malloc(_size * sizeof(void*));
	if (NULL == queue->m_items)
	{
		free(queue);
		return NULL;
	}

	queue->m_size = _size;
	queue->m_head = 0;
	queue->m_tail = 0;
	sem_init(&queue->m_empty, 0, _size);
	sem_init(&queue->m_full, 0, 0);
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
	sem_destroy(&_queue->m_full);
	sem_destroy(&_queue->m_empty);

	free(_queue->m_items);
	_queue->m_items = NULL;
	free(_queue);
}

ProtectedQueueResult ProtectedQueueInsert(ProtectedQueue* _queue, void* _item)
{
	if(!_queue)
	{
		return QUEUE_NOT_INITIALIZED;
	}

	sem_wait(&_queue->m_empty);
	pthread_mutex_lock(&_queue->m_mutex);

	_queue->m_items[_queue->m_head] = _item;
	_queue->m_head = (_queue->m_head + 1) % _queue->m_size;

	pthread_mutex_unlock(&_queue->m_mutex);
	sem_post(&_queue->m_full);

	return QUEUE_OK;
}

ProtectedQueueResult ProtectedQueueRemove(ProtectedQueue* _queue, void** _item)
{
	if(!_queue)
	{
		return QUEUE_NOT_INITIALIZED;
	}

	sem_wait(&_queue->m_full);
	pthread_mutex_lock(&_queue->m_mutex);

	*_item = _queue->m_items[_queue->m_tail];
	_queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;

	pthread_mutex_unlock(&_queue->m_mutex);
	sem_post(&_queue->m_empty);
	
	return QUEUE_OK;
}

int ProtectedQueueIsEmpty(ProtectedQueue* _queue)
{
	int sval;

	if(!_queue)
	{
		return 1;
	}
	
	sem_getvalue(&_queue->m_empty, &sval);

	return (sval) ? 0 : 1;
}




















