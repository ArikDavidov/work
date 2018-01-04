#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include <sys/epoll.h>
#include <tr1/memory>
#include <vector>

namespace net
{

class Socket;



class Selector
{
    static const int MAX_EVENTS = 10;
public:
    explicit Selector();
    ~Selector();
    
    void Add(std::tr1::shared_ptr<Socket> _sock);
    //void Remove();
    void WaitForActivity(std::vector<std::tr1::shared_ptr<Socket> >& _sockets,
                         std::vector<std::tr1::shared_ptr<Socket> >& _readySockets);

private:
    int m_epollfd;  // Sock_t / Handle?
    struct epoll_event m_events[MAX_EVENTS] ;
};



    
    
}  // namespace net

#endif // __SELECTOR_H__
