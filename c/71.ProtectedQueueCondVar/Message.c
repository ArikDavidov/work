#include "Message.h"

#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE			128


struct Message
{
	char		m_str[128];
	size_t		m_maxLen;
};


Message* MsgCreate(const char* _str)
{
	Message* msg = NULL;
	
	if (!_str)
	{
		return NULL;
	}
	
	msg = malloc(sizeof(Message));
	if (!msg)
	{
		return NULL;
	}
	
	msg->m_maxLen = MAX_BUFFER_SIZE;
	strncpy(msg->m_str, _str, msg->m_maxLen);
	
	return msg;
}

void MsgUpdate(Message* _msg, const char* _str)
{
	if (!_msg)
	{
		return;
	}
	
	strncpy(_msg->m_str, _str, _msg->m_maxLen);
}

void MsgDestroy(Message* _msg)
{
	if (!_msg)
	{
		return;
	}
	
	free(_msg);	
}



