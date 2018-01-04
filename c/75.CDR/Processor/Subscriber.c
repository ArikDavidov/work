#include "Subscriber.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#define SUCCESS 0
#define FAILURE 1


struct Subscriber
{
    unsigned int m_outgoingCallInNetwork;
    unsigned int m_incomigCallInNetwork;
    unsigned int m_outgoingCallOutNetwork;
    unsigned int m_incomigCallOutNetwork;
    unsigned int m_smsResiveInNetwork;
    unsigned int m_smsResiveOutNetwork;
    unsigned int m_smsSentInNetwork;
    unsigned int m_smsSentOutNetwork;
    double       m_mbDoun;
    double       m_mbUp;
};


Subscriber* SubscriberCreate()
{
	Subscriber* subscriber = NULL;
	
	subscriber = calloc(1, sizeof(Subscriber));
	if (!subscriber)
	{
		return	NULL;
	}

	return subscriber;
}

int SubscriberAddOutgoingCallInNetwork(Subscriber* _subscriber, unsigned int _duration)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	if (0 == _duration)
	{
		return SUCCESS;
	}
	
	_subscriber->m_outgoingCallInNetwork += _duration;

	return SUCCESS;
}

int SubscriberAddIncomigCallInNetwork(Subscriber* _subscriber, unsigned int _duration)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	if (0 == _duration)
	{
		return SUCCESS;
	}
	
	_subscriber->m_incomigCallInNetwork += _duration;

	return SUCCESS;
}


int SubscriberAddOutgoingSmsInNetwork(Subscriber* _subscriber, unsigned int _dummyArg)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	++_subscriber->m_smsSentInNetwork;

	return SUCCESS;
}


int SubscriberAddIncomingSmsInNetwork(Subscriber* _subscriber, unsigned int _dummyArg)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	++_subscriber->m_smsResiveInNetwork;

	return SUCCESS;
}

int SubscriberAddOutgoingCallOutNetwork(Subscriber* _subscriber, unsigned int _duration)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	if (0 == _duration)
	{
		return SUCCESS;
	}
	
	_subscriber->m_outgoingCallOutNetwork += _duration;

	return SUCCESS;
}


int SubscriberAddIncomigCallOutNetwork(Subscriber* _subscriber, unsigned int _duration)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	if (0 == _duration)
	{
		return SUCCESS;
	}
	
	_subscriber->m_incomigCallOutNetwork += _duration;

	return SUCCESS;
}


int SubscriberAddOutgoingSmsOutNetwork(Subscriber* _subscriber, unsigned int _dummyArg)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	++_subscriber->m_smsSentOutNetwork;

	return SUCCESS;
}


int SubscriberAddIncomingSmsOutNetwork(Subscriber* _subscriber, unsigned int _dummyArg)
{
	if (!_subscriber)
	{
		return FAILURE;
	}
	
	++_subscriber->m_smsResiveOutNetwork;

	return SUCCESS;
}

int SubscriberAddToDownloaded(Subscriber* _subscriber, double _megabytes)
{
	if (!_subscriber || 0 > _megabytes)
	{
		return FAILURE;
	}
	
	if (0 == _megabytes)
	{
		return SUCCESS;
	}
	
	_subscriber->m_mbDoun += _megabytes;
	
	return SUCCESS;
}

int SubscriberAddToUploaded(Subscriber* _subscriber, double _megabytes)
{
	if (!_subscriber || 0 > _megabytes)
	{
		return FAILURE;
	}

	if (0 == _megabytes)
	{
		return SUCCESS;
	}
	
	_subscriber->m_mbUp += _megabytes;
	
	return SUCCESS;
}

void SubscriberDestroy(Subscriber* _subscriber)
{
	if (!_subscriber)
	{
		return;
	}
	
	free(_subscriber);
}

void SubscriberPrint(Subscriber* _subscriber)
{
	assert(_subscriber);
	
	/* TODO mutex */
	printf("Subscriber: %d, %d, %d, %d, %d, %d, %d, %d, %.02lf, %.02lf\n", 
			_subscriber->m_outgoingCallInNetwork, _subscriber->m_incomigCallInNetwork,
			_subscriber->m_outgoingCallOutNetwork, _subscriber->m_incomigCallOutNetwork,
			_subscriber->m_smsResiveInNetwork, _subscriber->m_smsResiveOutNetwork,
			_subscriber->m_smsSentInNetwork, _subscriber->m_smsSentOutNetwork,
			_subscriber->m_mbDoun, _subscriber->m_mbUp);
	/* TODO mutex */
}

int SubscriberWriteToString(Subscriber* _subscriber, char* _buf)
{
	if (!_subscriber || !_buf)
	{
		return FAILURE;
	}

	sprintf(_buf, "%d, %d, %d, %d, %d, %d, %d, %d, %.02lf, %.02lf\n", 
			_subscriber->m_outgoingCallInNetwork, _subscriber->m_incomigCallInNetwork,
			_subscriber->m_outgoingCallOutNetwork, _subscriber->m_incomigCallOutNetwork,
			_subscriber->m_smsResiveInNetwork, _subscriber->m_smsResiveOutNetwork,
			_subscriber->m_smsSentInNetwork, _subscriber->m_smsSentOutNetwork,
			_subscriber->m_mbDoun, _subscriber->m_mbUp);

	return SUCCESS;
}


















