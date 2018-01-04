#include "Subscribers.h"
#include "Subscriber.h"
#include "MsgTransport.h"
#include "HashMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>	/* link with -pthread */
#include <assert.h>

#define WITHIN_THE_NETWORK(C)	!strcmp((C)->m_mccMnc, (C)->m_partyOperator)


#define	MUTEX_ARRAY_SIZE		100
#define HASH_MAP_CAPACITY		50000

#define MUTEX_INDEX(M)			(SubscribersHashFunc(M) % MUTEX_ARRAY_SIZE)
#define MUTEX(S, M)				&(S)->m_mutexArr[MUTEX_INDEX(M)]
#define WITHIN_THE_NETWORK(C)	!strcmp((C)->m_mccMnc, (C)->m_partyOperator)
#define INTERNET_USAGE(C)		(GPRS == (C)->m_callType)


typedef int (*agregateFunc)(Subscriber* _subscriber, unsigned int);

struct Subscribers
{
	HashMap*			m_map;
	pthread_mutex_t*	m_mutexArr;
};


static size_t SubscribersHashFunc(const void* _key)
{
	int sum;
	char* str = (char*)_key;
	
	assert(_key);
	
	for (sum = 0; '\0' != str[0]; ++str)
	{
		sum += (int)str[0];
	}
	
	return (size_t)sum;
}

static int SubscribersKeysEqualFunc(const void* _firstKey, const void* _secondKey)
{
	assert(_firstKey);
	assert(_secondKey);
		
	return !strcmp((char*)_firstKey, (char*)_secondKey);
}

static pthread_mutex_t* MutexArrayCreate(size_t _size)
{
	pthread_mutex_t* mutexArr = NULL;
	size_t i;
	
	assert(_size);
	
	mutexArr = malloc(_size * sizeof(pthread_mutex_t));
	if (!mutexArr)
	{
		return NULL;
	}
	
	for (i = 0; i < MUTEX_ARRAY_SIZE; ++i)
	{
		if (-1 == pthread_mutex_init(&mutexArr[i], NULL))
		{
			goto DESTROY_MUTEXES;
		}
	}

	return mutexArr;

	DESTROY_MUTEXES:
		perror("pthread_mutex_init");
		for (--i; i < MUTEX_ARRAY_SIZE; --i)
		{
			pthread_mutex_destroy(&mutexArr[i]);
		}
		
		free(mutexArr);
		
		return NULL;
}

static void MutexArrayDestroy(pthread_mutex_t* _mutexArr)
{
	size_t i;
	
	assert(_mutexArr);
	
	for (i = 0; i < MUTEX_ARRAY_SIZE; ++i)
	{
		pthread_mutex_destroy(&_mutexArr[i]);
	}
	
	free(_mutexArr);
}
		
Subscribers* SubscribersCreate()
{
	Subscribers* subscribers = NULL;
	
	subscribers = malloc(sizeof(Subscribers));
	if (!subscribers)
	{
		return NULL;
	}

	subscribers->m_mutexArr = MutexArrayCreate(MUTEX_ARRAY_SIZE);
	if (!subscribers->m_mutexArr)
	{
		goto MUTEX_DESTROY;
	}
	
	subscribers->m_map = HashMapCreate(HASH_MAP_CAPACITY, (HashFunction)SubscribersHashFunc,
									 SubscribersKeysEqualFunc);
	if (!subscribers->m_map)
	{
		goto HASH_MAP_DESTROY;
	}
	
	return subscribers;
	
	
	HASH_MAP_DESTROY:
	/*
		TODO
		HashMapDestroy(&subscribers->m_map, ......);
	*/
	
	MUTEX_DESTROY:
		MutexArrayDestroy(subscribers->m_mutexArr);
		free(subscribers);
		
		return NULL;	
}

Subscriber* SubscribersFindSubscriber(Subscribers* _subscribers, const char* _msisdn)
{
	Subscriber* subscriber = NULL;

	if (!_subscribers || !_msisdn)
	{
		return NULL;
	}
	
	pthread_mutex_lock(MUTEX(_subscribers, _msisdn));
	
	HashMapFind(_subscribers->m_map, (void*)_msisdn, (void**)&subscriber);
	/* TODO Check return */
	
	pthread_mutex_unlock(MUTEX(_subscribers, _msisdn));

	return subscriber;
}

static void* KeyCreate(const char* _msisdn)
{
	void* key;
	
	assert(_msisdn);
	
	key = malloc(16 + sizeof(char));
	if (!key)
	{
		return NULL;
	}
	
	strcpy(key, _msisdn);
	
	return key;
} 
/*
static void KeyDestroy(void* _key)
{
	assert(_key);
	
	free(_key);
}
*/
static Subscriber* CreateAndInsert(Subscribers* _subscribers, const char* _msisdn)
{
	Subscriber* subscriber = NULL;
	void* key;
	
	assert(_msisdn);
	
	if (!(subscriber = SubscriberCreate()))
	{
		return NULL;
	}		
	if (!(key = KeyCreate(_msisdn)))
	{
		/*TODO
		SubscriberDestroy(subscriber);
		*/
		return NULL;
	}
	
	HashMapInsert(_subscribers->m_map, key, (void*)subscriber);
	/* TODO Destroy if fails */
	
	return subscriber;
}

static Subscriber* GetSubscriber(Subscribers* _subscribers, const char* _msisdn)
{
	Subscriber* subscriber = NULL;
	MapResult ret;
	
	assert(_subscribers);
	assert(_msisdn);

	/*printf("SubscribersGetSubscriber\n");*/
	
	ret = HashMapFind(_subscribers->m_map, (void*)_msisdn, (void**)&subscriber);
	if (MAP_SUCCESS != ret && MAP_KEY_NOT_FOUND_ERROR != ret)
	{
		return NULL;
	}
	if (MAP_KEY_NOT_FOUND_ERROR == ret)
	{
		/*printf("MAP_KEY_NOT_FOUND_ERROR\n");*/

		if (!(subscriber = CreateAndInsert(_subscribers, _msisdn)))
		{
			return NULL;
		}
	}

	return subscriber;
}



SubscribersResult SubscribersProcess(Subscribers* _subscribers, const Cdr* _cdr)
{
	Subscriber* subscriber = NULL;
	agregateFunc AgregateWithinTheNetwork[] = {SubscriberAddOutgoingCallInNetwork,
											   SubscriberAddIncomigCallInNetwork,
											   SubscriberAddOutgoingSmsInNetwork,
											   SubscriberAddIncomingSmsInNetwork};
								 
	agregateFunc AgregateOutsideTheNetwork[] = {SubscriberAddOutgoingCallOutNetwork,
												SubscriberAddIncomigCallOutNetwork,
												SubscriberAddOutgoingSmsOutNetwork,
												SubscriberAddIncomingSmsOutNetwork};
	
	/*printf("SubscribersProcess\n");*/
	
	if (!_subscribers)
	{
		return SUBSCRIBERS_UNINITIALIZED_ERROR;
	}
	if (!_cdr)
	{
		return SUBSCRIBERS_INV_ARG_ERROR;
	}	
	
	pthread_mutex_lock(MUTEX(_subscribers, _cdr));
	
	subscriber = GetSubscriber(_subscribers, _cdr->m_msisdn);
	if (!subscriber)
	{
		printf("SUBSCRIBERS_ALLOCATION_ERROR\n");
		pthread_mutex_unlock(MUTEX(_subscribers, _cdr));
		return SUBSCRIBERS_ALLOCATION_ERROR;
	}
	
	if (INTERNET_USAGE(_cdr))
	{
		SubscriberAddToDownloaded(subscriber, _cdr->m_download);
		SubscriberAddToUploaded(subscriber, _cdr->m_upload);
	}
	else if (WITHIN_THE_NETWORK(_cdr))
	{
		AgregateWithinTheNetwork[_cdr->m_callType](subscriber, _cdr->m_duration);
	}
	else
	{
		AgregateOutsideTheNetwork[_cdr->m_callType](subscriber, _cdr->m_duration);
	}

	pthread_mutex_unlock(MUTEX(_subscribers, _cdr));
	
	return SUBSCRIBERS_SUCCESS;
}


void SubscribersDestroy(Subscribers* _subscriber);
/*
	Destroy all Keys
	Destroy all Operator totals
	MutexArrayDestroy
	map destroy
*/

void SubscribersPrint(Subscribers* _subscriber);
/*
	map for each
		print subscriber
*/

void SubscribersWrite(Subscribers* _subscriber/*, fd*/);
/*
	map for each
		write subscriber
*/		



void SubscribersWriteSubscriberToString(Subscribers* _subscribers, char* _msisdn,
										Subscriber* _subscriber, char* _buf)
{
	if (!_subscribers || !_msisdn || !_subscriber ||!_buf)
	{
		return;
	}

	pthread_mutex_lock(MUTEX(_subscribers, _msisdn));

	SubscriberWriteToString(_subscriber, _buf);
	
	pthread_mutex_unlock(MUTEX(_subscribers, _msisdn));
}




