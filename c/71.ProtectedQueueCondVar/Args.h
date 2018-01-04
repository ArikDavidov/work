#ifndef __ARGS_H__
#define __ARGS_H__

#include <stddef.h>

typedef struct InParams		/* size_t */
{
	int	m_nProducers;
	int	m_nConsumers;
	int	m_nMsgs;
	int	m_qSize;
} InParams;


void ArgsParser(int argc, char *argv[], InParams* _params);


#endif /* #ifndef __ARGS_H__ */

