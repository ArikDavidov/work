#include "ListeningSocket.h"
#include "Sock_t.h"

#include <arpa/inet.h>  // inet_ntoa
#include <stdexcept>
#include <string.h>     // strerror
#include <errno.h>

namespace net
{

ListeningSocket::ListeningSocket(uint16_t _port, int _backLog)
: m_addrLen(sizeof(m_peerSin))
{
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0)
    {
        throw std::runtime_error(std::string
                                 ("ListeningSocket ctor: socket() failed: ") 
                                 + strerror(errno));
    }
    
    SetToNonBolocking();
    
    int optval = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, 
                   &optval, sizeof(optval)) < 0)
    {
        throw std::runtime_error(std::string
                                 ("ListeningSocket ctor: reuse failed: ") 
                                 + strerror(errno));
    }    
    
    std::fill((char*)&m_sin, (char*)&m_sin + sizeof(m_sin), 0);
    
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = INADDR_ANY;
    m_sin.sin_port = htons(_port);
    
    if (bind(m_sock, (struct sockaddr*)&m_sin, sizeof(m_sin)) < 0)
    {
        throw std::runtime_error(std::string
                                 ("ListeningSocket ctor: bind failed: ") 
                                 + strerror(errno));
    }    

    if (listen(m_sock, _backLog) < 0)
    {
        throw std::runtime_error(std::string
                                 ("ListeningSocket ctor: listen failed: ") 
                                 + strerror(errno));
    }
}

ListeningSocket::~ListeningSocket()
{

}

//bool ListeningSocket::Accept(std::tr1::shared_ptr<PeerSocket> _sock)
std::tr1::shared_ptr<PeerSocket> ListeningSocket::Accept()
{
    Sock_t client;

    client = accept(m_sock, (struct sockaddr*)&m_peerSin, &m_addrLen);
    if (client <= 2)
    {
//        if (errno == EAGAIN || errno == EWOULDBLOCK)
//        {
//            // We have processed all incoming connections.
//            return false;
//        }
        
        throw std::runtime_error(std::string
                                 ("ListeningSocket Accept: accept failed: ") 
                                 + strerror(errno));
    }

    std::string addr = inet_ntoa(m_peerSin.sin_addr);
    uint16_t port = ntohs(m_peerSin.sin_port);
    
    return std::tr1::shared_ptr<PeerSocket>(new PeerSocket(client, addr, port));
//    return true;
}


}  // namespace net



