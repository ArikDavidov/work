#include "Operator.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 0
#define FAILURE 1

struct Operator
{
	/* TODO mutex */
	unsigned int	m_totalVoiceTo;		/**< total outgoing voice call durations to operator     */
	unsigned int	m_totalVoiceFrom;	/**< total incoming voice call durations from operator   */
	unsigned int	m_totalSmsTo;		/**< total number of outgoing SMS messages to operator   */
	unsigned int	m_totalSmsFrom;		/**< total number of incoming SMS messages from operator */
};


Operator* OperatorCreate()
{
	Operator* operator = NULL;

	operator = malloc(sizeof(Operator));
	if (!operator)
	{
		return	NULL;
	}

	/* TODO mutex */
	operator->m_totalVoiceFrom    = 0;
	operator->m_totalVoiceTo      = 0;
	operator->m_totalSmsFrom      = 0;
	operator->m_totalSmsTo        = 0;

	return operator;
}

void OperatorDestroy(Operator* _operator)
{
	if(!_operator)
	{
		return;
	}
	
	printf("OperatorDestroy\n");

	free(_operator);	
}

int OperatorAddCallToOutgoing(Operator* _operator, unsigned int _duration)
{
	if (!_operator)
	{
		return FAILURE;
	}
	
	/*printf("OperatorAddCallToOutgoing\n");*/
	_operator->m_totalVoiceTo += _duration;
	/*OperatorPrint(_operator);*/
	
	return SUCCESS;
}

int OperatorAddCallToIncoming(Operator* _operator, unsigned int _duration)
{
	if (!_operator)
	{
		return FAILURE;
	}
	
	/*printf("OperatorAddCallToIncoming\n");*/
	_operator->m_totalVoiceFrom += _duration;
	/*OperatorPrint(_operator);*/
		
	return SUCCESS;
}

int OperatorAddSmsToOutgoing(Operator* _operator)
{
	if (!_operator)
	{
		return FAILURE;
	}

	/*printf("OperatorAddSmsToOutgoing\n");*/
	++_operator->m_totalSmsTo;
	/*OperatorPrint(_operator);*/
	
	return SUCCESS;
}

int OperatorAddSmsToIncoming(Operator* _operator)
{
	if (!_operator)
	{
		return FAILURE;
	}
	
	/*printf("OperatorAddSmsToIncoming\n");*/
	++_operator->m_totalSmsFrom;
	/*OperatorPrint(_operator);*/
	
	return SUCCESS;
}

void OperatorPrint(Operator* _operator)
{
	assert(_operator);

	printf("Operator: %d, %d, %d, %d\n", _operator->m_totalVoiceTo,
			_operator->m_totalVoiceFrom, _operator->m_totalSmsTo,
			_operator->m_totalSmsFrom);

}

int OperatorWriteToString(Operator* _operator, char* _buf)
{
	if (!_operator || !_buf)
	{
		return FAILURE;
	}

	sprintf(_buf, "%d, %d, %d, %d\n", _operator->m_totalVoiceTo,
			_operator->m_totalVoiceFrom, _operator->m_totalSmsTo,
			_operator->m_totalSmsFrom);

	return SUCCESS;
}








