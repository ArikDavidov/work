#ifndef __COMM_SOCKET_H__
#define __COMM_SOCKET_H__

#include "Socket.h"
#include "Message.h"
#include <string>

namespace net
{

class CommSocket : public Socket
{
public:
    explicit CommSocket();
    virtual ~CommSocket() = 0;

    void Receive(Message& _msg);
    void Send(Message& _msg);

};

    



}  // namespace net

#endif // __COMM_SOCKET_H__


