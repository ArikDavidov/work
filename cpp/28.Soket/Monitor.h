#ifndef __MONITOR_H__
#define __MONITOR_H__

#include "Socket.h"
#include "Timestamp.h"

// #include <set>
#include <vector>
#include <deque>
#include <tr1/memory>
#include <sys/select.h>     /* FD_SET, FD_ISSET, FD_ZERO macros */

namespace net
{


class Monitor  //, private noncopyable 
{
    static const int MAX_FD = 1023;
public:
    explicit Monitor();
    ~Monitor();
	
	void Add(std::tr1::shared_ptr<Socket> _sock, Timestamp _timestamp);
    void Remove(std::tr1::shared_ptr<Socket> _sock);
    std::size_t Size() const;
    
    Timestamp WaitForActivity(std::tr1::shared_ptr<std::vector
                                   <std::tr1::shared_ptr<Socket> > > _readySockets);

private:
	void DisconectZombies(const Timestamp& _ts);

    std::deque<std::pair<Timestamp, std::tr1::shared_ptr<Socket> > > m_sockets;
    fd_set m_readfds;
};


inline std::size_t Monitor::Size() const
{
	return m_sockets.size();
}

class SockPred {
public:
    SockPred(std::tr1::shared_ptr<Socket> _sock)
    : m_sock(_sock) { }
    bool operator()(std::pair<Timestamp, std::tr1::shared_ptr<Socket> > _pair) {
      return m_sock == _pair.second;
    }
    std::tr1::shared_ptr<Socket> m_sock;
};

}   // namespace net

#endif // __MONITOR_H__


