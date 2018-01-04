#ifndef __CONSUMERS_H__
#define __CONSUMERS_H__

#include <pthread.h>
#include <semaphore.h>


typedef struct Consumers Consumers;


Consumers* ConsumersCreate(size_t _numOfConsumers, void* (*_consumerRoutine)(void *));

void ConsumersJoin(Consumers* _consumers);


#endif	/* #ifndef __CONSUMERS_H__ */




