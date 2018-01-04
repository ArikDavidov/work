#ifndef __CONNECTED_SOCKET_H__
#define __CONNECTED_SOCKET_H__

#include "CommSocket.h"

#include <string>

namespace net
{


class ConnectedSocket : public CommSocket
{
public:
    explicit ConnectedSocket(std::string _addr,uint16_t _port);
    virtual ~ConnectedSocket();
    
//    void Receive(Message& _msg);
//    void Send(Message& _msg);

private:
    struct sockaddr_in m_sin;
};

    
    
}  // namespace net

#endif // __CONNECTED_SOCKET_H__



//#include <netinet/in.h>     /* uint16_t */

