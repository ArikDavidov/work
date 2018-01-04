#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include <unistd.h>				/* useconds_t */
#include <sys/types.h>			/* pid_t */
#include <linux/limits.h>		/* PATH_MAX */

#define MAX_TEXT_LENGTH		256


typedef struct InParams
{
	int			m_createMQ;
	int			m_deleteMQ;
	int			m_nMsgs;
	int			m_verbosity;
	useconds_t	m_speed;
	char		m_ftokPathName[PATH_MAX];
} InParams;

/*
typedef struct InParams InParams;
typedef struct MsgBuf MsgBuf;

struct MsgBuf
{
	long	m_type;
	{
		pid_t	m_pid;
		int		m_MsgNum;
		char	m_text[MAX_TEXT_SIZE];
	} m_data;
};
*/
typedef struct MsgBuf
{
    long m_type;
    char m_text[MAX_TEXT_LENGTH];
} MsgBuf;


void ArgsParser(int argc, char* argv[], InParams* _params);

int  MsgQCreate(char* _pathName, int _createMQ, int _verbocity);
int  MsgQOpen(char* _pathName, int _verbocity);
int  MsgQSend(int _qid, long _type, MsgBuf* _myMsgBuf, int _verbocity);
int  MsgQReciveNoWait(int _qid, long _type, MsgBuf* _myMsgBuf, int _verbocity);
int  MsgQRecive(int _qid, long _type, MsgBuf* _myMsgBuf, int _verbocity);
void MsgQDestroy(int _qid, int _verbocity);
void MsgQDestroyAtExit();

void MsgQPrint(char* _direction, MsgBuf* _myMsgBuf);


#endif /* #ifndef __MESSAGE_QUEUE_H__ */

