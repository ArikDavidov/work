#include "CommSocket.h"

#include <stdexcept>
#include <errno.h>
#include <string.h>     // strerror

namespace net
{

CommSocket::CommSocket()
{
}

CommSocket::~CommSocket()
{
}

void CommSocket::Send(Message& _msg)
{
    ssize_t sentBytes = send(m_sock, _msg.m_data, _msg.m_size, MSG_NOSIGNAL);
    if (sentBytes < 0)
    {
        throw std::runtime_error(std::string
                                 ("CommSocket::Send: send failed: ") 
                                 + strerror(errno));
    }
}

void CommSocket::Receive(Message& _msg)
{
    ssize_t readBytes = recv(m_sock, _msg.m_data, _msg.m_size - 1, 0);
    if (readBytes == 0)
    {
        throw std::runtime_error("CommSocket::Recive: peer performed shutdown");
    }
    else if (readBytes < 0)
    {
        throw std::runtime_error(std::string
                                 ("CommSocket::Recive: recv failed: ") 
                                 + strerror(errno));
    }
}






}  // namespace net
