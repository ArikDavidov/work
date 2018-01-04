#ifndef __CONSUMERS_H__
#define __CONSUMERS_H__

#include "Context.h"


typedef struct Consumers Consumers;


Consumers* ConsumersCreate(size_t _numOfConsumers, Context* _context);

void ConsumerRoutine(Context* _context);

void ConsumersDestroy(Consumers* _consumers);

void ConsumersJoin(Consumers* _consumers);


#endif	/* #ifndef __CONSUMERS_H__ */




