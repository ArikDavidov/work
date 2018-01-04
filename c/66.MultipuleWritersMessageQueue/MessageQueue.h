#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include <unistd.h>			/* useconds_t */
#include <sys/types.h>		/* pid_t */
#include <linux/limits.h>	/* PATH_MAX */

#define MAX_TEXT_SIZE		256

typedef struct InParams InParams;
typedef struct MsgBuf MsgBuf;

struct InParams
{
	int			m_createMQ;
	int			m_deleteMQ;
	int			m_nMsgs;
	int			m_verbosity;
	useconds_t	m_speed;
	char		m_ftokPathName[PATH_MAX];
};

struct MsgBuf
{
	long	m_type;
	pid_t	m_pid;
	/*int		m_MsgNum;*/
	char	m_text[MAX_TEXT_SIZE];
};

int ArgsParser(int argc, char *argv[], InParams* _params);

void InitBuf(void* _buf, size_t _dataSize);

int OpenMessageQ(char* _pathName, int _createMQ);

int MessageQSend(int _qid, long _type, MsgBuf* _myMsgBuf);

int MsgQReciveNoWait(int _qid, MsgBuf* _myMsgBuf, long _type);

int MessageQRecive(int _qid, long _type, MsgBuf* _myMsgBuf);

void MessageQDestroy(int _qid);


#endif /* #ifndef __MESSAGE_QUEUE_H__ */

