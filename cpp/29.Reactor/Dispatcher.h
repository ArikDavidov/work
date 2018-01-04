#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <map>
#include <tr1/memory>

namespace net
{

class IHandler;



class Dispatcher
{
public:
    explicit Dispatcher();
    ~Dispatcher();

    void RegisterHandler(std::tr1::shared_ptr<IHandler> _handler);
private:
    std::map<std::tr1::shared_ptr<Socket>,
             std::tr1::shared_ptr<IHandler> > m_handlers;
    
};


}   // namespace net

#endif // __DISPATCHER_H__


