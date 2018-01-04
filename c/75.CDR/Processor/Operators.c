#include "Operators.h"
#include "Operator.h"
#include "MsgTransport.h"
#include "HashMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>	/* link with -pthread */
#include <assert.h>


#define	MUTEX_ARRAY_SIZE		100
#define HASH_MAP_CAPACITY		100000

#define MCC_MNC_LENGTH			6

//#define MUTEX_INDEX(C)			(OperatorsHashFunc((C)->m_partyOperator) % MUTEX_ARRAY_SIZE)
#define MUTEX_INDEX(P)			(OperatorsHashFunc(P) % MUTEX_ARRAY_SIZE)
#define MUTEX(O, P)				&(O)->m_mutexArr[MUTEX_INDEX(P)]
#define WITHIN_THE_NETWORK(C)	!strcmp((C)->m_mccMnc, (C)->m_partyOperator)
#define INTERNET_USAGE(C)		(GPRS == (C)->m_callType)

struct Operators
{
	HashMap*			m_map;
	pthread_mutex_t*	m_mutexArr;
};


static size_t OperatorsHashFunc(const void* _key)
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

static int OperatorsKeysEqualFunc(const void* _firstKey, const void* _secondKey)
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

Operators* OperatorsCreate()
{
	Operators* operators = NULL;
	
	operators = malloc(sizeof(Operators));
	if (!operators)
	{
		return NULL;
	}

	operators->m_mutexArr = MutexArrayCreate(MUTEX_ARRAY_SIZE);
	if (!operators->m_mutexArr)
	{
		goto MUTEX_DESTROY;
	}
	
	operators->m_map = HashMapCreate(HASH_MAP_CAPACITY, (HashFunction)OperatorsHashFunc,
									 OperatorsKeysEqualFunc);
	if (!operators->m_map)
	{
		goto HASH_MAP_DESTROY;
	}
	
	return operators;
	
	
	HASH_MAP_DESTROY:
	/*
		TODO
		HashMapDestroy(&operators->m_map, ......);
	*/
	
	MUTEX_DESTROY:
		MutexArrayDestroy(operators->m_mutexArr);
		free(operators);
		
		return NULL;	
}

Operator* OperatorsFindOperator(Operators* _operators, const char* _partyOperator)
{
	Operator* operator = NULL;

	if (!_operators || !_partyOperator)
	{
		return NULL;
	}

	pthread_mutex_lock(MUTEX(_operators, _partyOperator));

	HashMapFind(_operators->m_map, (void*)_partyOperator, (void**)&operator);
	/* TODO Check return */

	pthread_mutex_unlock(MUTEX(_operators, _partyOperator));

	return operator;
}

static void* KeyCreate(const char* _partyOperator)
{
	void* key;
	
	assert(_partyOperator);
	
	key = malloc(MCC_MNC_LENGTH + sizeof(char));
	if (!key)
	{
		return NULL;
	}
	
	strcpy(key, _partyOperator);
	
	return key;
} 
/*
static void KeyDestroy(void* _key)
{
	assert(_key);
	
	free(_key);
}
*/
static Operator* CreateAndInsert(Operators* _operators, const char* _partyOperator)
{
	Operator* operator = NULL;
	void* key;
	
	assert(_partyOperator);
	
	if (!(operator = OperatorCreate()))
	{
		return NULL;
	}		
	if (!(key = KeyCreate(_partyOperator)))
	{
		OperatorDestroy(operator);
		return NULL;
	}
	
	HashMapInsert(_operators->m_map, key, (void*)operator);
	/* TODO Destroy if fails */
	
	return operator;
}

static Operator* GetOperator(Operators* _operators, const char* _partyOperator)
{
	Operator* operator = NULL;
	MapResult ret;
	
	assert(_operators);
	assert(_partyOperator);

	/*printf("OperatorsGetOperator\n");*/
	
	ret = HashMapFind(_operators->m_map, (void*)_partyOperator, (void**)&operator);
	if (MAP_SUCCESS != ret && MAP_KEY_NOT_FOUND_ERROR != ret)
	{
		return NULL;
	}
	if (MAP_KEY_NOT_FOUND_ERROR == ret)
	{
		/*printf("MAP_KEY_NOT_FOUND_ERROR\n");*/

		if (!(operator = CreateAndInsert(_operators, _partyOperator)))
		{
			return NULL;
		}
	}
	/*printf("GetOperator: returnning operator\n");*/
	return operator;
}

OperatorsResult OperatorsProcess(Operators* _operators, const Cdr* _cdr)
{
	Operator* operator = NULL;

	/*printf("OperatorsProcess\n");*/
	
	if (!_operators)
	{
		return OPERATORS_UNINITIALIZED_ERROR;
	}
	if (!_cdr)
	{
		return OPERATORS_INV_ARG_ERROR;
	}	
	
	if (INTERNET_USAGE(_cdr) || WITHIN_THE_NETWORK(_cdr))
	{
		/*printf("INTERNET_USAGE or WITHIN_THE_NETWORK\n");*/
		return OPERATORS_SUCCESS;
	}
	/*	
	printf("MccMnc: %s\n", _cdr->m_mccMnc);
	printf("PartyOperator: %s\n", _cdr->m_partyOperator);
	*/
	pthread_mutex_lock(MUTEX(_operators, _cdr->m_partyOperator));
	
	operator = GetOperator(_operators, _cdr->m_partyOperator);
	if (!operator)
	{
		printf("OPERATORS_ALLOCATION_ERROR\n");
		return OPERATORS_ALLOCATION_ERROR;
	}
	
	/*
	((Cdr*)_cdr)->m_callType = 3;
	printf("_cdr->m_callType = %d\n", _cdr->m_callType);
	CdrPrint(_cdr);
	*/

	switch (_cdr->m_callType)
	{
		case MOC:
			OperatorAddCallToOutgoing(operator, _cdr->m_duration);	break;
		case MTC:
			OperatorAddCallToIncoming(operator, _cdr->m_duration);	break;
		case SMS_MO:
			OperatorAddSmsToOutgoing(operator);						break;
		case SMS_MT:
			OperatorAddSmsToIncoming(operator);						break;
		default:
			assert(0);
	}
	
	pthread_mutex_unlock(MUTEX(_operators, _cdr->m_partyOperator));
	
	return OPERATORS_SUCCESS;
}


void OperatorsDestroy(Operators* _operator);
/*
	Destroy all Keys
	Destroy all Operator totals
	MutexArrayDestroy
	map destroy
*/

void OperatorsWriteOperatorToString(Operators* _operators, char* _partyOperator,
										Operator* _operator, char* _buf)
{
	if (!_operators || !_partyOperator || !_operator ||!_buf)
	{
		return;
	}

	pthread_mutex_lock(MUTEX(_operators, _partyOperator));

	OperatorWriteToString(_operator, _buf/*, _bufSize*/);
	
	pthread_mutex_unlock(MUTEX(_operators, _partyOperator));
}

void OperatorsPrintAllOperator(Operators* _operators);
/*
	map for each
		print operator


*/

void OperatorsWrite(Operators* _operator/*, fd*/);
/*
	map for each
		write operator
*/






