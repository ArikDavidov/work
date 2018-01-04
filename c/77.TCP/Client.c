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
    struct sockaddr_in sin;
    ssize_t sentBytes;
    ssize_t readBytes;
    char data[] = "Zero bug approach";
    size_t dataLen = strlen(data) + 1;
    char buffer[BUFFER_SIZE];

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s IP port\n", argv[0]);
		abort();
	}

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        abort();
    }
    
    memset(&sin, 0, sizeof(sin));
    
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    sin.sin_port = htons((uint16_t)atoi(argv[2]));
    
    if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0)
    {
        perror("connection failed");
        abort();
    }
    
    printf("client is running\n");

    while (1)
    {    
        sentBytes = send(sock, data, dataLen, 0);
        if (sentBytes < 0)
        {
            perror("send failed");
            abort();
        }

        sin.sin_addr.s_addr = INADDR_ANY;
        readBytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (readBytes == 0)
        {
            printf("Connection Closed: Socket %d\n", sock);
            break;
        }
        else if (readBytes < 0)
        {
            perror("recv failed");
            abort();
        }
    
        printf("Client RCVD: %s\n", buffer);
    }
    
    close(sock);
    
    return 0;
}




