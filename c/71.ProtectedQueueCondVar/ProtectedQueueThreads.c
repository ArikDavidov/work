#include "ProtectedQueue.h"
#include "Producers.h"
#include "Consumers.h"
#include "Context.h"
#include "Args.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>		/* Compile with -pthread */

#define DEFAULT_NUM_OF_PRODUCERS	15
#define DEFAULT_NUM_OF_CONSUMERS	8
#define DEFAULT_NUM_OF_MESSAGES		5
#define DEFAULT_QUEUE_SIZE			5
#define DEFAULT_PARAMS				{DEFAULT_NUM_OF_PRODUCERS, DEFAULT_NUM_OF_CONSUMERS, \
									 DEFAULT_NUM_OF_MESSAGES, DEFAULT_QUEUE_SIZE}


static Context* ContextCreare(ProtectedQueue* _requestsQ, ProtectedQueue* _replyQ, int _nMsgs)
{
	Context* context = NULL;

	context = malloc(sizeof(Context));
	if (!context)
	{
		return NULL;
	}

	context->m_requestsQ = _requestsQ;
	context->m_replyQ = _replyQ;
	context->m_nMsgs = _nMsgs;	
	
	return context;
}

static void ContextDestroy(Context* _context)
{
	free(_context);	
}

int main(int argc, char *argv[])
{
	InParams params = DEFAULT_PARAMS;
	ProtectedQueue* requestsQ = NULL;
	ProtectedQueue* replyQ = NULL;
	Producers* producers = NULL;
	Consumers* consumers = NULL;
	Context* context = NULL;
	
	ArgsParser(argc, argv, &params);
	
	requestsQ = ProtectedQueueCreate((size_t)params.m_qSize);
	replyQ    = ProtectedQueueCreate((size_t)params.m_qSize);
	
	context   = ContextCreare(requestsQ, replyQ, params.m_nMsgs);
	
	consumers = ConsumersCreate((size_t)params.m_nProducers, (void*)context);
	producers = ProducersCreate((size_t)params.m_nConsumers, (void*)context);
	
	ProducersJoin(producers);
	/*StopConsumers(consumers);*/
	ConsumersJoin(consumers);

	ContextDestroy(context);
	
	ProducersDestroy(producers);
	ConsumersDestroy(consumers);
	
	ProtectedQueueDestroy(replyQ);
	ProtectedQueueDestroy(requestsQ);
	
	return 0;
}


