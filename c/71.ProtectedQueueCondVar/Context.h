#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "ProtectedQueue.h"


typedef struct Context
{
	ProtectedQueue*	m_requestsQ;
	ProtectedQueue*	m_replyQ;
	int				m_nMsgs;
} Context;
	


#endif	/* #ifndef __CONTEXT_H__ */
