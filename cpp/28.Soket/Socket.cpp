#include "Socket.h"

#include <unistd.h>     // close
#include <fcntl.h>      // fcntl, F_GETFL, F_SETFL
#include <string.h>     // strerror
#include <stdexcept>
#include <errno.h>


namespace net
{


Socket::Socket()
{
}

Socket::~Socket()
{
    close(m_sock);
}

void Socket::SetToNonBolocking()
{
    int flags;

    if ((flags = fcntl(m_sock, F_GETFL)) < 0)
    {
        throw std::runtime_error
                (std::string("Socket::SetToNonBolocking: fcntl F_GETFL failed: ") 
                 + strerror(errno));
    }
    if (fcntl(m_sock, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        throw std::runtime_error
                (std::string("Socket::SetToNonBolocking: fcntl F_SETFL failed: ") 
                 + strerror(errno));
    }
}


}  // namespace advcpp
