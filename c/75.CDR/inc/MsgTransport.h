#ifndef __MSG_TRANSPORT_H__
#define __MSG_TRANSPORT_H__

#include "CDR.h"

typedef struct MsgTransportCdrBuf
{
    long	m_type;
    Cdr		m_cdr;
} MsgTransportBuf;


int MsgTransportCreate();
int MsgTransportOpen();
int MsgTransportSendCdr(int _mtid, MsgTransportBuf* _buf);
int MsgTransportGetCdr(int _mtid, MsgTransportBuf* _buf);
int MsgTransportSendQuery(int _mtid, MsgTransportBuf* _buf);
int MsgTransportGetQuery(int _mtid, MsgTransportBuf* _buf);
int MsgTransportSendReply(int _mtid, MsgTransportBuf* _buf);
int MsgTransportGetReply(int _mtid, MsgTransportBuf* _buf);

#endif /* #ifndef __MSG_TRANSPORT_H__ */


