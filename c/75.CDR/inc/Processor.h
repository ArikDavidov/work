#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "Subscribers.h"
#include "Operators.h"

#include <pthread.h>


#define PROCESSOR_THREADS_NUM	8


typedef struct Processor
{
	Subscribers*	m_subscribers;
	Operators*		m_operators;
	pthread_t		m_processorThreads[PROCESSOR_THREADS_NUM];
	pthread_t		m_cgfThread;
	int				m_mtid;
	int				m_pauseMode;
	int				m_shutDownMode;
} Processor;


#endif /* #ifndef __PROCESSOR_H__ */


