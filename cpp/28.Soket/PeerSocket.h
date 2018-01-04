#ifndef __PEER_SOCKET_H__
#define __PEER_SOCKET_H__

#include "CommSocket.h"
#include "Message.h"
#include <string>

namespace net
{

class PeerSocket : public CommSocket //, private noncopyable 
{
public:
    explicit PeerSocket(Sock_t _sock, std::string _addr, uint16_t _port); // make private + friend
    virtual ~PeerSocket();

//    void Receive(Message& _msg);
//    void Send(Message& _msg);

private:
    std::string m_addr;
    uint16_t m_port;
};

    



}  // namespace net

#endif // __PEER_SOCKET_H__


