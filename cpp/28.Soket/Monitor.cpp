#include "Monitor.h"
#include "Timestamp.h"

#include <string.h>     // strerror
#include <algorithm>    // find_if
#include <errno.h>

namespace net
{


Monitor::Monitor()
{
    FD_ZERO(&m_readfds);
}

Monitor::~Monitor()
{
}

void Monitor::Add(std::tr1::shared_ptr<Socket> _sock, Timestamp _timestamp)
{
    m_sockets.push_front(std::make_pair(std::tr1::shared_ptr<Socket> ,_sock));
    FD_SET(_sock->NativeSocket(), &m_readfds);
}

void Monitor::Remove(std::tr1::shared_ptr<Socket> _sock)
{
    FD_CLR(_sock->NativeSocket(), &m_readfds);
    m_sockets.erase(std::find_if(m_sockets.begin(), m_sockets.end(), SockPred(_sock)));
}

void Monitor::DisconectZombies(const Timestamp& _ts)
{
    while (m_sockets.back().first <= _ts)
    {
        FD_CLR(m_sockets.back().second->NativeSocket(), &m_readfds);
        m_sockets.pop_back();
    }
}

Timestamp Monitor::WaitForActivity(std::tr1::shared_ptr<std::vector
                                   <std::tr1::shared_ptr<Socket> > > _readySockets)
{
    fd_set tmpReadfds = m_readfds;

    int activity = select(MAX_FD + 1, &tmpReadfds, 0, 0, 0); //TODO m_clients.max_size 
    if (activity < 0 && errno != EINTR)
    {
        throw std::runtime_error(std::string
                                 ("Monitor WaitForActivity: select failed: ") 
                                 + strerror(errno));
    }

    Timestamp timestamp;
    std::tr1::shared_ptr<Socket> spSocket;
    
    if (activity)
    {
        std::deque<std::pair<Timestamp, std::tr1::shared_ptr<Socket> > >::iterator it;
        for (it = m_sockets.begin(); it != m_sockets.end() && activity; )
        {
            if (FD_ISSET((it->second)->NativeSocket(), &tmpReadfds))
            {
                --activity;

                spSocket = it->second;
                _readySockets->push_back(spSocket);
                
                it = m_sockets.erase(it);
                m_sockets.push_front(std::make_pair(timestamp, spSocket));
            }
            else
            {
                ++it;
            }
        }
    }
    else
    {
        DisconectZombies(timestamp);
    }       
    
    return timestamp;
}


}   // namespace net





