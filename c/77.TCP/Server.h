#ifndef __SERVER_H__
#define __SERVER_H__

#include <netinet/in.h>     /* uint16_t */


typedef struct Server Server;

typedef struct ClientData {
    int m_id;
    uint16_t m_port;
    char m_ip[16];
} ClientData;

typedef void (*WellcomeFn)(ClientData* _clientData, void* _context);
typedef size_t (*CallbackFn)(void* _inBuf, size_t _inSize,
	                         void* _outBuf, size_t _outSize, void* _context);


Server* ServerCreate(uint16_t _port);

void ServerRun(Server* _server, WellcomeFn _wellcome, void* _wellcomeContext,
               CallbackFn _fn, void* _fnContext);

int ServerSend(int _clientId, void* _buf, size_t _len);

void ServerDestroy(Server* _server);


#endif /* __SERVER_H__ */


