#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "Sock_t.h"

#include <netinet/in.h>     /* sockaddr_in, INADDR_ANY */
#include <tr1/memory>


namespace net
{


class Socket
{
public:
    explicit Socket();
    virtual ~Socket() = 0;
    
    void SetToNonBolocking();

    struct Less {
        virtual bool operator() (std::tr1::shared_ptr<Socket> _left,
                                 std::tr1::shared_ptr<Socket> _right) const {
            return _left->m_sock < _right->m_sock;
        }
    };

    int NativeSocket() const;

protected:
    Sock_t m_sock;
};



inline std::ostream& operator<<(std::ostream& _os, const Socket& _sock)
{
    _os << _sock.NativeSocket();

    return _os;
}


inline int Socket::NativeSocket() const
{
    return m_sock.NativeSocket();
}

// inline int& Socket::NativeSocket()
// {
// 	return m_sock.NativeSocket();
// }



    
}  // namespace advcpp

#endif // __SOCKET_H__


