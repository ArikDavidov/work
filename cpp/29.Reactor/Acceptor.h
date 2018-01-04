#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "IHandler.h"
// #include "ListeningSocket.h"
// #include "Dispatcher.h"
// #include "DeMux.h"

#include <tr1/memory>

namespace net
{

class ListeningSocket;
class Dispatcher;
class DeMux;


class Acceptor : public IHandler , public std::tr1::enable_shared_from_this<Acceptor>
{
public:
    explicit Acceptor(std::tr1::shared_ptr<ListeningSocket> _listeningSock,
                      std::tr1::shared_ptr<Dispatcher> _dispatcher,
                      std::tr1::shared_ptr<DeMux> _deMux);
    virtual ~Acceptor();
    
    virtual void HandleEvent();

private:
    std::tr1::shared_ptr<ListeningSocket> m_listeningSock;
    std::tr1::shared_ptr<Dispatcher> m_dispatcher;
    std::tr1::shared_ptr<DeMux> m_deMux;
};



}  // namespace net

#endif // __ACCEPTOR_H__




