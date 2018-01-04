#ifndef __SERVER_H__
#define __SERVER_H__

#include "ListeningSocket.h"
#include "Monitor.h"

#include <netinet/in.h>     /* uint16_t */
#include <vector>


namespace net
{

class PeerSocket;
//class ListeningSocket;


class Server
{
    static const std::size_t BUFFER_SIZE = 4096;
    static const std::size_t MAX_NUM_OF_CLIENTS = 1000;
    
public:
    explicit Server(uint16_t _port, int _backLog);
    ~Server();
    
    void Run();

private:
    void CheckNewClients(Timestamp _timestamp);
    void CheckExistingClients(Message& _inMsg, Message& _outMsg);
    
    std::tr1::shared_ptr<ListeningSocket> m_listeningSock;
    std::tr1::shared_ptr<std::vector
          <std::tr1::shared_ptr<Socket> > > m_readySockets;
    Monitor m_monitor;
};

    
    
    
    
}  // namespace net

#endif // __SERVER_H__


