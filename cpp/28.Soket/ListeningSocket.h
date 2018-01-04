#ifndef __LISTENING_SOCKET_H__
#define __LISTENING_SOCKET_H__

#include "Socket.h"
#include "PeerSocket.h"

#include <tr1/memory>   // std::tr1::shared_ptr


namespace net
{

class ListeningSocket : public Socket
{
public:
    explicit ListeningSocket(uint16_t _port, int _backLog);
    virtual ~ListeningSocket();

    std::tr1::shared_ptr<PeerSocket> Accept();
    
private:
    struct sockaddr_in m_sin;
    struct sockaddr_in m_peerSin;
    socklen_t m_addrLen;
};

    

    
    
}  // namespace net

#endif // __LISTENING_SOCKET_H__


