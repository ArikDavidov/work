#include "ProtectedQueue.h"
#include "Producers.h"
#include "Consumers.h"
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


struct InParams
{
	int	m_nProducers;
	int	m_nConsumers;
	int	m_nMsgs;
	int	m_qSize;
};


int main(argc, argv[])
{
	InParams params = DEFAULT_PARAMS;
	Queue* requestsQ = NULL;
	Queue* replyQ = NULL;
	Producers* producers = NULL;
	Consumers* consumers = NULL;
	
	ArgsParser(argc, argv[], &params);
	
	requestsQ = QueueCreate(params->m_qSize);
	replyQ = QueueCreate(params->m_qSize);
	
	consumers = ConsumersCreate();
	producers = ProducerCreate();
	
	ProducerJoin(producers);
	ConsumersJoin(consumers);
	
	ProducerDestroy(producers);
	StopConsumers(consumers);
	ConsumersDestroy(consumers);
	
	QueueDestroy(replyQ);
	QueueDestroy(requestsQ);
	
	return 0;
}


