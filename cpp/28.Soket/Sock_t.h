#ifndef __SOKET_DESCRIPTOR_H__
#define __SOKET_DESCRIPTOR_H__

#include <iostream>
namespace net
{


class Sock_t
{
public:
    operator int() const {
        return m_sock;
    }
      
    Sock_t& operator=(const Sock_t& _sock) {
        m_sock = _sock.m_sock;
    }
    Sock_t& operator=(int _sock) {
        m_sock = _sock;
    }

    int NativeSocket() const;
    // int& NativeSocket();

private:
    int m_sock;
};
    

inline std::ostream& operator<<(std::ostream& _os, const Sock_t& _sock)
{
    _os << _sock.NativeSocket();

    return _os;
}

inline int Sock_t::NativeSocket() const
{
    return m_sock;
}

// inline int& Sock_t::NativeSocket()
// {
//     return m_sock;
// }




    
}  // namespace advcpp

#endif // __SOKET_DESCRIPTOR_H__


