#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__

#include "Guard.h"

#include <iostream>
#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
//Link with -pthread


template <class T>
class SafeQueue
{
public:
	explicit SafeQueue();
	virtual ~SafeQueue();
	
	void Push(const T& _element);
	T    Pop();

private:	
    SafeQueue(const SafeQueue&);
    SafeQueue& operator=(const SafeQueue&);

private:
	std::queue<T>   m_queue;
	sem_t           m_empty;
	pthread_mutex_t m_mutex;
};



template <class T>
SafeQueue<T>::SafeQueue()
{
	if (sem_init(&m_empty, 0, 0) == -1)
	{
		perror("sem_init");
		throw errno;
	}

	if (pthread_mutex_init(&m_mutex, 0) == -1)
	{
		sem_destroy(&m_empty);
		perror("pthread_mutex_init");
		throw errno;
	}
}


template <class T>
SafeQueue<T>::~SafeQueue()
{
	pthread_mutex_destroy(&m_mutex);
	sem_destroy(&m_empty);
	std::cout << "~SafeQueue" << std::endl;
}


template <class T>
void SafeQueue<T>::Push(const T& _element)
{
//	pthread_mutex_lock(&m_mutex);
    {
        Guard guard(&m_mutex);
	    // try?
	    m_queue.push(_element);
	}
//    pthread_mutex_unlock(&m_mutex);
	sem_post(&m_empty);
}

template <class T>
T SafeQueue<T>::Pop()
{
	sem_wait(&m_empty);
//	pthread_mutex_lock(&m_mutex);

    Guard guard(&m_mutex);
        
	T element = m_queue.front();
	m_queue.pop();
	
//    pthread_mutex_unlock(&m_mutex);
    
    return element;
}


#endif	// __SAFE_QUEUE_H__


