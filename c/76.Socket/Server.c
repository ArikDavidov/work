#include <sys/types.h>      /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>     /* sockaddr_in, INADDR_ANY */
#include <arpa/inet.h>      /* inet_ntoa */

#include <stdlib.h>         /* abort */
#include <string.h>         /* memset */
#include <unistd.h>         /* sleep */
#include <stdio.h>


int main (int argc, char *argv[])
{
    int sock;
    struct sockaddr_in sin;
    socklen_t sin_len = sizeof(sin);
    char buffer[4096];
    
    char data[] = "Zero bug approach";
    size_t dataLen = strlen(data) + 1;
    ssize_t readBytes;
    ssize_t sentBytes;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        abort();
    }
    
    memset(&sin, 0, sizeof(sin));
    
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(atoi(argv[1]));
    
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
        
        printf("RCVD from IP: %s : %s\n", inet_ntoa(sin.sin_addr),  buffer);

        
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




