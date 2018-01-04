#include "Server.h"
#include "List.h"

#include <sys/types.h>      /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>     /* sockaddr_in, INADDR_ANY */
#include <arpa/inet.h>      /* inet_ntoa */
#include <sys/select.h>     /* FD_SET, FD_ISSET, FD_ZERO macros */
#include <sys/time.h>       /*  */
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include <stdlib.h>         /* abort */
#include <string.h>         /* memset */
#include <unistd.h>         /* sleep */
#include <stdio.h>          /* F_GETFL, F_SETFL */

#define BACK_LOG 32
#define BUFFER_SIZE 4096
#define MAX_NUM_OF_CLIENTS 1000
#define MAX_FD 1023


struct Server
{
    struct sockaddr_in m_sin;
    int m_listeningSock;
    List* m_clients;
    fd_set m_readfds;
    WelcomeFn m_welcome;
    CallbackFn m_appFunc;
    NotifyDisconnectFn m_notifyDisconnect;
    void* m_context;
    struct timeval m_timeout;
};

struct Client
{
    int m_sock;
    struct timeval m_expiration;
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


Server* ServerCreate(uint16_t _port, /*size_t _maxClients, int _backlog*/ WelcomeFn _welcome, CallbackFn _appFunc,
                     NotifyDisconnectFn _notifyDisconnect, void* _context)
{
    int optval = 1;
    Server* server = NULL;
    
    if (!_appFunc)
    {
        fprintf(stderr, "ServerCreate failed: CallbackFn missing\n");
        abort();
    }
    
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

    FD_ZERO(&server->m_readfds);
    FD_SET(0, &server->m_readfds);
    FD_SET(server->m_listeningSock, &server->m_readfds);
    
    server->m_welcome = _welcome;
    server->m_appFunc = _appFunc;
    server->m_notifyDisconnect = _notifyDisconnect;
    server->m_context =  _context;
    
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
        printf("client disconnected: Socket %d\n", _sock);
        return -1;
    }
    else if (readBytes < 0)
    {
        perror("recv failed");
        return -1;
    }
    
    return 1;
} 

int ServerSend(int _sock, void* _buf, size_t _len)
{
    ssize_t sentBytes;
    
    assert(_buf);
    
    sentBytes = send(_sock, _buf, _len, MSG_NOSIGNAL);
    if (sentBytes < 0)
    {
        perror("send failed");
        return -1;
    }
    assert(sentBytes);
    
    return 0;
}

static void SocketClose(Server* _server, ListItr _it)
{
    int* pClient = ListItrRemove(_it);//////////////////////////////
    
    _server->m_notifyDisconnect(*pClient, _server->m_context);
    FD_CLR(*pClient, &_server->m_readfds);
    DisconectClient(pClient, NULL);
}

static void CheckCurrentClients(Server* _server, fd_set* _tmpReadfds, int _activity,
                                void* _inBuf, size_t _inBufSize,
                                void* _outBuf, size_t _outBufSize)
{
    int status;
    size_t len;
    int* pClient;
    ListItr it = ListItrBegin(_server->m_clients);
    ListItr end = ListItrEnd(_server->m_clients);
        
    for (; !ListItrEquals(it, end) && _activity; it = ListItrNext(it))
    {
        pClient = ListItrGet(it);

        if (!FD_ISSET(*pClient, _tmpReadfds))
        {
            continue;
        }
        
        --_activity;
        status = SocketRecive(*pClient, _inBuf, _inBufSize);
        if (status < 0)
        {
            SocketClose(_server, it);
            continue;
        }

        assert(status);
    
        len = _server->m_appFunc(_inBuf, _inBufSize, _outBuf, _outBufSize, _server->m_context);

        status = ServerSend(*pClient, _outBuf, len);
        if (status < 0)
        {
            SocketClose(_server, it);
        }        
    }
}

static void CheckNewClients(Server* _server)
{
    int client;
    int* pClient = NULL;
    ClientData clientData;
    struct sockaddr_in clientSin;
    socklen_t addrLen = sizeof(clientSin);

    while ((client = accept(_server->m_listeningSock, (struct sockaddr*)&clientSin, 
                            &addrLen)) > 2)
    {
        if (MAX_NUM_OF_CLIENTS <= ListCountItems(_server->m_clients))
        {
            fprintf(stderr, "To many connections. Closing socket\n");
            close(client);
            continue;
        }

        clientData.m_id = client;
        clientData.m_port = ntohs(clientSin.sin_port);
        strcpy(clientData.m_ip, inet_ntoa(clientSin.sin_addr));

        _server->m_welcome(&clientData, _server->m_context);

        pClient = malloc(sizeof(client));
        *pClient = client;
        ListPushTail(_server->m_clients, pClient);
        
        FD_SET(client, &_server->m_readfds);
    }
}


/* TODO macro */
static struct timeval* GetNextExpiration(List* _clients)
{
    assert(_clients);

    struct Client* pClient = ListItrGet(ListItrEnd(_clients));
    
    return &pClient->m_expiration;
}

static struct timeval* CalculateTimeout(struct timeval* _nextExpiration, struct timeval* _timeout)
{
    struct timeval current;
    
    assert(_nextExpiration);
    assert(_timeout);
        

    gettimeofday(&current, NULL);
    // printf("_timeout: %ld.%06ld\n", _nextExpiration->tv_sec, _nextExpiration->tv_usec);
    // printf("_timeout: %ld.%06ld\n", _timeout->tv_sec, _timeout->tv_usec);
    printf("current: %ld.%06ld\n", current.tv_sec, current.tv_usec);
    
    if (timercmp(_nextExpiration, &current, >=))
    {
        timersub(&current, _nextExpiration, _timeout);
    }
    else
    {
        /* select() will return immediately */
        timerclear(_timeout);
    }
    
    // printf("_timeout: %ld.%06ld\n", _timeout->tv_sec, _timeout->tv_usec);
    
    return _timeout;
}

static struct timeval* GetTimeout(List* _clients, struct timeval* _timeout)
{
    struct timeval* nextExpiration;

    assert(_clients);
    assert(_timeout);

    if (ListIsEmpty(_clients))
    {
        return NULL;    /* select() will block */
    }

    // NEXT_EXPIRATION(_clients)
    nextExpiration = GetNextExpiration(_clients);

    return CalculateTimeout(nextExpiration, _timeout);
}

void ServerRun(Server* _server)
{
    char inBuf[BUFFER_SIZE];
    char outBuf[BUFFER_SIZE];
    fd_set tmp;
    int activity;
    struct timeval timeout;
    struct timeval* pTimeout;
    
    while (1)
    {
        tmp = _server->m_readfds;
        activity = 0;
        pTimeout = GetTimeout(_server->m_clients, &timeout);
        
        activity = select(MAX_FD + 1, &tmp, NULL, NULL, pTimeout);
        if (activity < 0 && errno != EINTR) 
        {
            perror("select");
            return;
        }
        if (FD_ISSET(0, &tmp))
        {
            return;
        }
        if (0 != activity)
        {
            //calcTimeStamp();
            if (FD_ISSET(_server->m_listeningSock, &tmp))
            {
                CheckNewClients(_server);
                --activity;
            }
            
            if (activity)
            {
                CheckCurrentClients(_server, &tmp, activity,
                                    inBuf, BUFFER_SIZE, outBuf, BUFFER_SIZE);
            }
        }
        else
        {
            // deal with Zombies...
        }      
    }
}




