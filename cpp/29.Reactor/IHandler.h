#ifndef __I_HANDLER_H__
#define __I_HANDLER_H__

// #include "Socket.h"

#include <tr1/memory>

namespace net
{

class Socket;


class IHandler
{
public:
    virtual ~IHandler();
    
    // virtual int HandleAccept() = 0;
    // virtual int HandleInput() = 0;
    // virtual int HandleOutput() = 0;
    // virtual int HandleTimeout() = 0;
    // virtual int HandleClose() = 0;
    virtual void HandleEvent() = 0;
    
    virtual std::tr1::shared_ptr<Socket> GetSocket() const = 0;
};


}   // namespace net

#endif // __I_HANDLER_H__


