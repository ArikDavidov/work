

Selector::Selector
{
    m_epollfd = epoll_create1(0);
    if (m_epollfd < 0) 
    {
        throw std::runtime_error(std::string
                                 ("DeMux ctor: epoll_create1 failed: ") 
                                 + strerror(errno));
    }
}

Selector::~Selector
{
    close(m_epollfd);
}

Selector::Add(std::tr1::shared_ptr<Socket> _sock)
{
    struct epoll_event ev;
    
    ev.events = EPOLLIN | EPOLLET;  // Edge Triggered
    ev.data.fd = _sock->NativeSock();
    
    if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, _sock->NativeSock(), &ev) < 0)
    {
        throw std::runtime_error(std::string
                                 ("Selector Add: epoll_ctl failed: ")
                                 + strerror(errno));
    }
}

void WaitForActivity(std::vector<std::tr1::shared_ptr<Socket> >& _sockets,
                     std::vector<std::tr1::shared_ptr<Socket> >& _readySockets)
{
   nfds = epoll_wait(epollfd, m_events, MAX_EVENTS, -1);
   if (nfds == -1) {
       perror("epoll_wait");
       exit(EXIT_FAILURE);
   }
}




