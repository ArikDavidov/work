#include "Server.h"
#include "Message.h"
#include "PeerSocket.h"
#include "Timestamp.h"

#include <string.h>     // strlen
#include <arpa/inet.h>  // inet_ntoa
#include <algorithm>    // find
#include <iostream>
#include <vector>

namespace net
{

Server::Server(uint16_t _port, int _backLog)    //maxNumOfClients
: m_listeningSock(new ListeningSocket(_port, _backLog))
, m_readySockets(new std::vector<std::tr1::shared_ptr<Socket> >)
{
    m_monitor.Add(m_listeningSock, Timestamp());
}

Server::~Server()
{
}

void Server::Run()
{
    char buffer[BUFFER_SIZE];
    Message inMsg;
    inMsg.m_data = buffer;
    inMsg.m_size = BUFFER_SIZE - 1;

    char str[] = "You've been served";
    Message outMsg;
    outMsg.m_data = str;
    outMsg.m_size = strlen(str) + 1;
    
    Timestamp timestamp;

    while (true)
    {    
        timestamp = m_monitor.WaitForActivity(m_readySockets);

        CheckNewClients(timestamp);
        CheckExistingClients(inMsg, outMsg);
    }
}

void Server::CheckNewClients(Timestamp _timestamp)
{
    std::vector<std::tr1::shared_ptr<Socket> >::iterator it;
    it = find(m_readySockets->begin(), m_readySockets->end(), m_listeningSock);
    if (it == m_readySockets->end())
    {
        return;
    }
    
    // CheckExistingClients needs to recieve
    // m_readySockets with only PeerSockets in it.
    m_readySockets->erase(it);

    std::tr1::shared_ptr<PeerSocket> client;
    while (true)
    {
        try {
            client = m_listeningSock->Accept();
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return;
        }
        if (MAX_NUM_OF_CLIENTS <= m_monitor.Size())
        {
            std::cerr << "To many connections. Closing socket" << std::endl;
            continue;
        }

        m_monitor.Add(client, _timestamp);
    }
}

void Server::CheckExistingClients(Message& _inMsg, Message& _outMsg)
{
    static int i = 0;
    
    std::vector<std::tr1::shared_ptr<Socket> >::iterator it;
    for (it = m_readySockets->begin(); it != m_readySockets->end(); ++it)
    {
        try {
            (std::tr1::static_pointer_cast<PeerSocket>(*it))->Receive(_inMsg);

            //AppFunctor(_inMsg, _outMsg)....    
            std::cout << "Server RCVD msg# " << i++ << ": " << (char*)_inMsg.m_data << std::endl;

            (std::tr1::static_pointer_cast<PeerSocket>(*it))->Send(_inMsg);
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Server CheckExistingClients: Removing client.." << std::endl;
            m_monitor.Remove(*it);
        }
    }
}


}  // namespace net




