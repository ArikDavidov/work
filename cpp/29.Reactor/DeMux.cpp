#include "DeMux.h"
#include "Socket.h"

#include <sys/epoll.h>
#include <stdexcept>
#include <string>
#include <string.h>     // strerror
#include <errno.h>


namespace net
{


DeMux::DeMux()
: m_listeningSock(new ListeningSocket(_port, _backLog))
{
    m_selector.Add(m_listeningSock);
}

DeMux::~DeMux()
{
}

void DeMux::Add(std::tr1::shared_ptr<Socket> _sock)
{
    m_sockets.push_back(_sock);
    
    //FD_SET(_sock->NativeSocket(), &m_readfds);
    m_selector.Add(_sock);
}
    

//int epoll_create1(int flags);
//int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
//int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);



void DeMux::WaitForActivity(std::vector<std::tr1::shared_ptr<Socket> >& _readySockets)
{


}
//    fd_set tmpReadfds = m_readfds;

//    int activity = select(MAX_FD + 1, &tmpReadfds, 0, 0, 0); //TODO m_clients.max_size 
//    if (activity < 0 && errno != EINTR)
//    {
//        throw std::runtime_error(std::string
//                                 ("DeMux WaitForActivity: select failed: ") 
//                                 + strerror(errno));
//    }

//    std::tr1::shared_ptr<Socket> spSocket;
//    
//    std::deque<std::pair<Timestamp, std::tr1::shared_ptr<Socket> > >::iterator it;
//    for (it = m_sockets.begin(); it != m_sockets.end() && activity; )
//    {
//        if (FD_ISSET((it->second)->NativeSocket(), &tmpReadfds))
//        {
//            --activity;

//            spSocket = it->second;
//            _readySockets->push_back(spSocket);
//            
//            it = m_sockets.erase(it);
//            m_sockets.push_front(std::make_pair(timestamp, spSocket));
//        }
//        else
//        {
//            ++it;
//        }
//    }




}  // namespace net

auto n = epoll_wait(epollfd, events.data(), ::max_events, -1);
for (int i = 0; i < n; ++i)
{
    if (events[i].events & EPOLLERR ||
        events[i].events & EPOLLHUP ||
        !(events[i].events & EPOLLIN)) // error
    {
        std::cerr << "[E] epoll event error\n";
        close(events[i].data.fd);
    }
    else if (socketfd == events[i].data.fd) // new connection
    {
        while (::accept_connection(socketfd, event, epollfd)) {}
    }
    else // data to read
    {
        auto fd = events[i].data.fd;
        while (::read_data(fd)) {}
    }
}




