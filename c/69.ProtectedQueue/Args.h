#ifndef __ARGS_H__
#define __ARGS_H__


struct InParams
{
	int	m_nProducers;
	int	m_nConsumers;
	int	m_nMsgs;
	int	m_qSize;
};


void ArgsParser(int argc, char *argv[], InParams* _params,
				const char* _options, const char* _usage)


#endif /* #ifndef __ARGS_H__ */

