#include "ConnectedSocket.h"

#include <arpa/inet.h>  // inet_addr
#include <stdexcept>
#include <errno.h>
#include <string.h>     // strerror
#include <algorithm>


namespace net
{

ConnectedSocket::ConnectedSocket(std::string _addr, uint16_t _port)
{
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0)
    {
        throw std::runtime_error("ConnectedSocket ctor: socket() failed");
    }
    
    // memset(&m_sin, 0, sizeof(m_sin));
    std::fill((char*)&m_sin, (char*)&m_sin + sizeof(m_sin), 0);
    
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = inet_addr(_addr.c_str());
    m_sin.sin_port = htons(_port);
    
    if (connect(m_sock, (struct sockaddr*)&m_sin, sizeof(m_sin)) < 0)
    {
        throw std::runtime_error(std::string
                                 ("ConnectedSocket ctor: connection failed: ")
                                 + strerror(errno));
    }
}

ConnectedSocket::~ConnectedSocket()
{

}



}  // namespace net


