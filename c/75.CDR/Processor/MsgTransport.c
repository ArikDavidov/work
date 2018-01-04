#include "MessageQueue.h"
#include "MsgTransport.h"
#include "CDR.h"


#define FTOK_PATH_NAME		"/tmp"
#define CDR_TYPE			1
#define QUERY_TYPE			2
#define REPLY_TYPE			3

/*
struct MsgTransport
{
	m_mtidCdr;
	m_cdrBuf;
	m_cgfBuf;
}

struct CdrBuf
{
    long		m_type;
    Cdr	m_cdr;
};
*/

int MsgTransportCreate()
{
	return MsgQCreate(FTOK_PATH_NAME, 1, 1);
}

int MsgTransportOpen()
{
	return MsgQOpen(FTOK_PATH_NAME, 1);
}

int MsgTransportSendCdr(int _mtid, MsgTransportBuf* _buf)
{
	return MsgQSend(_mtid, CDR_TYPE, (MsgBuf*)_buf, 0);
}

int MsgTransportGetCdr(int _mtid, MsgTransportBuf* _buf)
{
	return MsgQRecive(_mtid, CDR_TYPE, (MsgBuf*)_buf, 0);
}

int MsgTransportSendQuery(int _mtid, MsgTransportBuf* _buf)
{
	return MsgQSend(_mtid, QUERY_TYPE, (MsgBuf*)_buf, 0);
}

int MsgTransportGetQuery(int _mtid, MsgTransportBuf* _buf)
{
	return MsgQRecive(_mtid, QUERY_TYPE, (MsgBuf*)_buf, 0);
}

int MsgTransportSendReply(int _mtid, MsgTransportBuf* _buf)
{
	return MsgQSend(_mtid, REPLY_TYPE, (MsgBuf*)_buf, 0);
}

int MsgTransportGetReply(int _mtid, MsgTransportBuf* _buf)
{
	return MsgQRecive(_mtid, REPLY_TYPE, (MsgBuf*)_buf, 0);
}


/*
int MsgTransportListenToEvents(processor->m_mtid, &buf)
{
	
}
*/












