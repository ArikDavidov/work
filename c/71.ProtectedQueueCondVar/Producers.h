#ifndef __PRODUCERS_H__
#define __PRODUCERS_H__

#include "Context.h"


typedef struct Producers Producers;

	
Producers* ProducersCreate(size_t _numOfProducers, void* _context);

void* ProducerRoutine(Context* _context);

void ProducersJoin(Producers* _producers);

void ProducersDestroy(Producers* _producers);


#endif	/* #ifndef __PRODUCERS_H__ */




