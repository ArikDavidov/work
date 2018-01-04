#ifndef __CLIENT_H__
#define __CLIENT_H__

/* ========================	*/

typedef struct Client Client;

typedef enum ClientErrors
{
	CLIENT_OK,
	CLIENT_INVARG,
	CLIENT_FAILED
}ClientErrors;

/* ========================	*/

Client* ClientCreate();

void ClientDestroy(Client* _client);

ClientErrors ClientConnect(Client* _client, char* _ip, short _port);

ClientErrors ClientDisconnect(Client* _client);

ClientErrors ClientSendMessage(Client* _client, void* _stream, size_t _len);

ClientErrors ClientRecieveMessage(Client* _client, void* _stream, size_t _len);

#endif /* __CLIENT_H__ */

