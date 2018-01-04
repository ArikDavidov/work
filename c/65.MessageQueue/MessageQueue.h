

typedef struct 
{
	int m_createMQ;
	int m_deleteMQ;
	int m_nMsgs;
	int m_eof;
} InParams;


typedef struct  
{
	long	m_type;
	pid_t	m_pid;
	char	m_text[256];
} MsgBuf;






