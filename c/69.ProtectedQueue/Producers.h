#ifndef __PRODUCERS_H__
#define __PRODUCERS_H__

#include <pthread.h>
#include <semaphore.h>


typedef struct Producers Producers;
	
	
Producers* ProducersCreate(size_t _numOfProducers, void* (*_producerRoutine)(void *));

void ProducersJoin(Producers* _producers);

	


#endif	/* #ifndef __PRODUCERS_H__ */




