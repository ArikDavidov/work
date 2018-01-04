#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Client.h"

#define MAX_MSG_SIZE 4096
#define CLIENT_AMOUNT 1000
#define SEND_CHANCE 40
#define DISCONNECT_CHANCE 10
#define CONNECT_CHANCE 30

int main(int argc, char *argv[])
{
    Client* client[CLIENT_AMOUNT];
    int clientConnected[CLIENT_AMOUNT];
    int i, randNum;
    char ip[32];
    short port;
    char stream[MAX_MSG_SIZE] = "";
	char serverSendMsg[] = "Client message num: ";
    
    strcpy(ip, argv[1]);
   port = atoi(argv[2]);
    
    printf("Open Clients\n");
    for (i = 0; i < CLIENT_AMOUNT; ++i)
    {
        client[i] = ClientCreate();
        if (!client[i])
        {
            return 0;
        }
        clientConnected[i] = 0;
    }
    
    for(;;)
    {
        for (i = 0; i < CLIENT_AMOUNT; ++i)
        {
            randNum = rand() % 101;
            printf("randNum %d, client #%d\n", randNum, i);
            if (clientConnected[i])
            {
                if (randNum < SEND_CHANCE)
                {
                    serverSendMsg[19] = i;
                    printf("Client #%d sending\n", i);
                    if (CLIENT_OK != ClientSendMessage(client[i], serverSendMsg, strlen(serverSendMsg)+1))
                    {
                        printf("Client #%d failed sending\n", i);
                        clientConnected[i] = 0;
                        continue;
                    }
                    printf("Client #%d recieving\n", i);
                    if (CLIENT_OK != ClientRecieveMessage(client[i], stream, MAX_MSG_SIZE))
                    {
                        printf("Client #%d failed recivieng\n", i);
                        continue;
                    }
                    printf("Client #%d recieved: %s\n", i, (char*)stream);
                }
                else if (randNum > (100 - DISCONNECT_CHANCE))
                {
                    printf("Client #%d disconnecting\n", i);
                    ClientDisconnect(client[i]);
                    clientConnected[i] = 0;
                }
            }
            else
            {
                if (randNum < CONNECT_CHANCE)
                {
                    printf("Client #%d connecting\n", i);
                    if (ClientConnect(client[i], ip, port) == CLIENT_OK)
                    {
                        clientConnected[i] = 1;
                    }
                }
            }
        }
    }
    
    printf("Client Destroy\n");
    for (i = 0; i < CLIENT_AMOUNT; ++i)
    {
        ClientDestroy(client[i]);
    }
    
    return 0;
}
