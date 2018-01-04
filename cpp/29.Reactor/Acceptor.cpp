#include "Acceptor.h"
#include "ListeningSocket.h"
#include "Dispatcher.h"
#include "DeMux.h"

#include <stdexcept>

namespace net
{


Acceptor::Acceptor(std::tr1::shared_ptr<ListeningSocket> _listeningSock,
                   std::tr1::shared_ptr<Dispatcher> _dispatcher,
                   std::tr1::shared_ptr<DeMux> _deMux)
: m_listeningSock(_listeningSock)
, m_dispatcher(_dispatcher)
, m_deMux(_deMux)
{
    // TODO add ACCEPT_EVENT as parameter
    // TODO chek if posibol to use shared_from_this in ctor
    m_dispatcher->RegisterHandler(shared_from_this());
    m_deMux->Add(m_listeningSock);//////////////////////////????????
}

Acceptor::~Acceptor()
{
}

void Acceptor::HandleEvent()
{
    std::tr1::shared_ptr<PeerSocket> sock;
    std::tr1::shared_ptr<IHandler> handler;
    
    while (true)
    {
        try {
            sock = m_listeningSock->Accept();
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return;
        }

        handler = new MyHandler(sock);
        // handler = std::tr1::shared_ptr<IHandler>(new MyHandler(sock));

        m_dispatcher->RegisterHandler(handler);

        m_deMux->Add(sock);
    }
}

//    event.data.fd = infd;
//    event.events = EPOLLIN | EPOLLET;
//    s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
//    if (s == -1)
//    {
//        perror ("epoll_ctl");
//        abort ();
//    }




//else if (sfd == events[i].data.fd)
//{
//  /* We have a notification on the listening socket, which
//     means one or more incoming connections. */
//  while (1)
//    {
//      struct sockaddr in_addr;
//      socklen_t in_len;
//      int infd;
//      char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

//      in_len = sizeof in_addr;
//      infd = accept (sfd, &in_addr, &in_len);
//      if (infd == -1)
//        {
//          if ((errno == EAGAIN) ||
//              (errno == EWOULDBLOCK))
//            {
//              /* We have processed all incoming
//                 connections. */
//              break;
//            }
//          else
//            {
//              perror ("accept");
//              break;
//            }
//        }

//      s = getnameinfo (&in_addr, in_len,
//                       hbuf, sizeof hbuf,
//                       sbuf, sizeof sbuf,
//                       NI_NUMERICHOST | NI_NUMERICSERV);
//      if (s == 0)
//        {
//          printf("Accepted connection on descriptor %d "
//                 "(host=%s, port=%s)\n", infd, hbuf, sbuf);
//        }

      /* Make the incoming socket non-blocking and add it to the
         list of fds to monitor. */
//      s = make_socket_non_blocking (infd);
//      if (s == -1)
//        abort ();

//      event.data.fd = infd;
//      event.events = EPOLLIN | EPOLLET;
//      s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
//      if (s == -1)
//        {
//          perror ("epoll_ctl");
//          abort ();
//        }
//    }
//  continue;
//}
            
            
}  // namespace net






            
