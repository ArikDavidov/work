#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Client.h"
#include <stdio.h>
#include <arpa/inet.h>

struct Client
{
    int m_socket;
    int m_isInit;
};

static int SocketInit()
{
    int tempSocket;
    
    tempSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tempSocket < 0)
    {
        perror("socket() failed");
        return 0;
    }
    
    return tempSocket;
}

static int ClientConnectPrivate(int _socketFD, char* _ip, short _port)
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(_ip);
    sin.sin_port = htons(_port);
    if(connect(_socketFD, (struct sockaddr*) &sin, sizeof(sin)) < 0) 
    {
        perror("connect() failed");
        return 0;
    }
    
    return 1;
}

static void SocketClose(int _socketFD)
{
    close(_socketFD);
}

Client* ClientCreate()
{
    Client* client;
    
    client = malloc(sizeof(Client));
    if (!client)
    {
        return 0;
    }
    
    return client;
}

void ClientDestroy(Client* _client)
{
    if (!_client)
    {
        return;
    }
    
    if (_client->m_isInit)
    {
        SocketClose(_client->m_socket);
    }
    free(_client);
}

ClientErrors ClientConnect(Client* _client, char* _ip, short _port)
{
    if (!_client)
    {
        return CLIENT_INVARG;
    }
    
    _client->m_socket = SocketInit();
    if (!(_client->m_socket))
    {
        return CLIENT_FAILED;
    }
    
    if (ClientConnectPrivate(_client->m_socket, _ip, _port) == 0)
    {
        SocketClose(_client->m_socket);
        return CLIENT_FAILED;
    }
    
    _client->m_isInit = 1;
    
    return CLIENT_OK;
}

ClientErrors ClientDisconnect(Client* _client)
{
    if (!_client)
    {
        return CLIENT_INVARG;
    }
    
    if (_client->m_isInit)
    {
        SocketClose(_client->m_socket);
        _client->m_isInit = 0;
    }
    
    return CLIENT_OK;
}

ClientErrors ClientSendMessage(Client* _client, void* _stream, size_t _len)
{
    int sent;
    
    if (!_client)
    {
        return CLIENT_INVARG;
    }
    
    if (!_client->m_isInit)
    {
        return CLIENT_FAILED;
    }
    
    sent = send(_client->m_socket, _stream, _len, MSG_NOSIGNAL);
    if (sent < 0)
    {
        SocketClose(_client->m_socket);
        _client->m_isInit = 0;
        return CLIENT_FAILED;
    }
    
    return CLIENT_OK;
}

ClientErrors ClientRecieveMessage(Client* _client, void* _stream, size_t _len)
{
    int read;
    
    if (!_client)
    {
        return CLIENT_INVARG;
    }
    
    if (!_client->m_isInit)
    {
        return CLIENT_FAILED;
    }
    
    read = recv(_client->m_socket, _stream, _len, 0);
    if (read == 0)
    {
        return CLIENT_FAILED;
    }
    else if (read < 0)
    {
        perror("recv() failed");
        return CLIENT_FAILED;
    }
    
    return CLIENT_OK;
}
