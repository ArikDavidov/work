#include <sys/types.h>      /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>     /* sockaddr_in, INADDR_ANY */
#include <arpa/inet.h>      /* inet_ntoa */

#include <stdlib.h>         /* abort */
#include <string.h>         /* memset */
#include <unistd.h>         /* sleep */
#include <stdio.h>

#define BUFFER_SIZE 4096
    
int
main (int argc, char *argv[])
{
    int sock;
    struct sockaddr_in6 sin;
    socklen_t sin_len = sizeof(sin);
    char buffer[BUFFER_SIZE];
    
    char data[] = "Zero bug approach";
    size_t dataLen = strlen(data) + 1;
    ssize_t readBytes;
    ssize_t sentBytes;
    char straddr[INET6_ADDRSTRLEN];
    
    sock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        abort();
    }
    
    memset(&sin, 0, sizeof(sin));

    sin.sin6_family = AF_INET6;
    sin.sin6_addr = in6addr_any;
    sin.sin6_port = htons(atoi(argv[1]));
    
    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0 )
    {
        perror("bind failed");
        abort();
    }

    while (1)
    {    
        readBytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                             (struct sockaddr*)&sin, &sin_len);
        
        if (readBytes < 0)
        {
            perror("recvfrom failed");
            abort();
        }
        
        inet_ntop(AF_INET6, &sin.sin6_addr, straddr, sizeof(straddr));
        printf("RCVD from IP: %s : %s\n", straddr,  buffer);
        
        sleep(1);
        
        sentBytes = sendto(sock, data, dataLen, 0, 
                           (struct sockaddr*)&sin, sizeof(sin));
        
        if (sentBytes < 0)
        {
            perror("sendto failed");
            abort();
        }
    }
  
    close(sock);
        
    return 0;
}




