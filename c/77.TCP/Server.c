#include "Server.h"
#include "List.h"

#include <sys/types.h>      /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>     /* sockaddr_in, INADDR_ANY */
#include <arpa/inet.h>      /* inet_ntoa */
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include <stdlib.h>         /* abort */
#include <string.h>         /* memset */
#include <unistd.h>         /* sleep */
#include <stdio.h>          

#define BACK_LOG 32
#define BUFFER_SIZE 4096
#define MAX_NUM_OF_CLIENTS 1000


struct Server
{
    struct sockaddr_in m_sin;
    int m_listeningSock;
    List* m_clients;
};


static int SocketSetToNonBolocking(int _sock)
{
    int flags;

    if ((flags = fcntl(_sock, F_GETFL)) < 0)
    {
        perror("fcntl F_GETFL failed");
        return -1;
    }
    if (fcntl(_sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        perror("fcntl F_SETFL failed");
        return -1;
    }
    
    return 0;
}

static int DisconectClient(void* _client,
                           __attribute__((unused))void* _dummy)
{
    assert(_client);
    
    close(*(int*)_client);
    free(_client);

    return 0;
}


Server* ServerCreate(uint16_t _port)
{
    int optval = 1;
    Server* server = NULL;
    
    server = malloc(sizeof(Server));
    if (NULL == server)
    {
        abort();
    }
    
    server->m_clients = ListCreate();
    if (NULL == server->m_clients)
    {
        goto FREE_SERVER;
    }
    
    server->m_listeningSock = socket(AF_INET, SOCK_STREAM, 0);
    if (server->m_listeningSock < 0)
    {
        perror("socket() failed");
        goto DESTROY_LIST;
    }
    
    if (SocketSetToNonBolocking(server->m_listeningSock) < 0)
    {
        goto CLOSE;
    }
    
    if (setsockopt(server->m_listeningSock, SOL_SOCKET, SO_REUSEADDR, 
                   &optval, sizeof(optval)) < 0)
    {
        perror("reuse failed");
    }

    memset(&server->m_sin, 0, sizeof(server->m_sin));
    server->m_sin.sin_family = AF_INET;
    server->m_sin.sin_addr.s_addr = INADDR_ANY;
    server->m_sin.sin_port = htons(_port);
    
    if (bind(server->m_listeningSock,
             (struct sockaddr*)&server->m_sin, sizeof(server->m_sin)) < 0)
    {
        perror("bind failed");
        goto CLOSE;
    }    

    if (listen(server->m_listeningSock, BACK_LOG) < 0)
    {
        perror("listen failed");
        goto CLOSE;
    }
    
    return server;
        
    CLOSE:
        close(server->m_listeningSock);
            
    DESTROY_LIST:
        ListDestroy(&server->m_clients, DisconectClient);
        
    FREE_SERVER:
        free(server);
        abort();
}

void ServerDestroy(Server* _server)
{
    if (!_server)
    {
        return;
    }

    ListDestroy(&_server->m_clients, DisconectClient);
    close(_server->m_listeningSock);
    free(_server);
}

static int SocketRecive(int _sock, char* _buf, size_t _bufSize)
{
    ssize_t readBytes;
    
    assert(_buf);

    readBytes = recv(_sock, _buf, _bufSize - 1, 0);
    if (readBytes == 0)
    {
        printf("client disconected: Socket %d\n", _sock);
        return -1;
    }
    else if (readBytes < 0)
    {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            perror("recv failed");
            return -1;
        }
        
        return 0;
    }
    
    return 1;
} 

int ServerSend(int _sock, void* _buf, size_t _len)
{
    ssize_t sentBytes;
    
    assert(_buf);
    
    sentBytes = send(_sock, _buf, _len, 0);
    if (sentBytes < 0)
    {
        perror("send failed");
        return -1;
    }
    assert(sentBytes);
    
    return 0;
}

static void CheckCurrentClients(List* _clients, CallbackFn AppFunc, void* _context,
                                void* _inBuf, size_t _inBufSize,
                                void* _outBuf, size_t _outBufSize)
{
    int status;
    size_t len;
    int* pClient;
    ListItr it = ListItrBegin(_clients);
    ListItr end = ListItrEnd(_clients);
    
    for (; !ListItrEquals(it, end); it = ListItrNext(it))
    {
        pClient = ListItrGet(it);

        status = SocketRecive(*pClient, _inBuf, _inBufSize);
        if (status < 0)
        {
            fprintf(stderr, "closed: Socket %d\n", *pClient);
            DisconectClient(pClient, NULL);
            ListItrRemove(it);
            continue;
        }
        if (status == 0)
        {
            continue;
        }
        
        len = AppFunc(_inBuf, _inBufSize, _outBuf, _outBufSize, _context);

        status = ServerSend(*pClient, _outBuf, len);
        if (status < 0)
        {
            fprintf(stderr, "closed: Socket %d\n", *pClient);
            DisconectClient(pClient, NULL);
            ListItrRemove(it);
        }
    }
}

static void CheckNewClients(int _listeningSock, List* _clients,
                            WellcomeFn _wellcome, void* _context)
{
    int client;
    int* pClient = NULL;
    ClientData clientData;
    struct sockaddr_in clientSin;
    socklen_t addrLen = sizeof(clientSin);
    
    while ((client = accept(_listeningSock, (struct sockaddr*)&clientSin,
                            &addrLen)) > 2)
    {
        if (MAX_NUM_OF_CLIENTS <= ListCountItems(_clients))
        {
            fprintf(stderr, "To many connections. Closing socket\n");
            close(client);
            continue;
        }

        if (SocketSetToNonBolocking(client) < 0)
        {
            fprintf(stderr, "SocketSetToNonBolocking failed. Closing socket\n");
            close(client);
            continue;
        }

        clientData.m_id = client;
        clientData.m_port = ntohs(clientSin.sin_port);
        strcpy(clientData.m_ip, inet_ntoa(clientSin.sin_addr));

        _wellcome(&clientData, _context);

        pClient = malloc(sizeof(client));
        *pClient = client;
        ListPushTail(_clients, pClient);
    }
}

void ServerRun(Server* _server, WellcomeFn _wellcome, void* _wellcomeContext,
               CallbackFn _fn, void* _fnContext)
{
    char inBuf[BUFFER_SIZE];
    char outBuf[BUFFER_SIZE];
    
    while (1)
    {
        CheckNewClients(_server->m_listeningSock, _server->m_clients,
                        _wellcome, _wellcomeContext);
        CheckCurrentClients(_server->m_clients, _fn, _fnContext,
                            inBuf, BUFFER_SIZE, outBuf, BUFFER_SIZE);
    }
}

    

