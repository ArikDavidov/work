#include "Server.h"

#include <sys/types.h>      /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>     /* sockaddr_in, INADDR_ANY */
#include <arpa/inet.h>      /* inet_ntoa */

#include <stdlib.h>         /* abort */
#include <string.h>         /* memset */
#include <unistd.h>         /* sleep */
#include <stdio.h>


void Wellcome(ClientData* _clientData, void* _context)
{
    printf("ClientId: %d, port: %d, ip: %s\n",
        _clientData->m_id, _clientData->m_port, _clientData->m_ip);
}

size_t Echo(void* _inBuf, size_t _inSize, void* _outBuf, size_t _outSize, void* _context)
{
    static int i = 0;
    
    //printf("Server RCVD msg# %d: %s\n", i++, (char*)_inBuf);
    strcpy((char*)_outBuf, _context);

    return strlen(_context);
}

void Notify(int _clientId, void* _context)
{
    printf("Notify: Client disconnected: %d\n", _clientId);
}

   
int main (int argc, char *argv[])
{
    uint16_t port;
    Server* server;
    char msg[] = "Zero bug approach";
    
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        abort();
    }
    
    port = (uint16_t)atoi(argv[1]);
    server = ServerCreate(port, Wellcome, Echo, Notify, msg);
    
    printf("server is running\n");
    ServerRun(server);

    ServerDestroy(server);

    return 0;
}




