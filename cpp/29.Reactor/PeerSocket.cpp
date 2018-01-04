#include "PeerSocket.h"
#include "Message.h"

#include <stdexcept>
#include <errno.h>
#include <string.h>     // strerror

namespace net
{


PeerSocket::PeerSocket(Sock_t _sock, std::string _addr, uint16_t _port)
: m_addr(_addr)
, m_port(_port)
{
    m_sock = _sock;
}

PeerSocket::~PeerSocket()
{
}






}  // namespace net


