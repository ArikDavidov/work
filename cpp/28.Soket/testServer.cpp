#include "Server.h"

#include <stdlib.h>     /* abort, atoi */
#include <iostream>

using namespace net;



int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " port" << std::endl;
        abort();
    }
    
    uint16_t port = (uint16_t)atoi(argv[1]);
    Server server(port, 32);

    std::cout << "server is running" << std::endl;
    
    server.Run();

    return 0;
}

//    try {
//        soket.Send(*pClient, _outBuf, len);
//    } catch (std::exception& e) {
//        cerr << e.what();
//        SocketClose(_server, it);
//    }



