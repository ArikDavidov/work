

void Handler::CheckExistingClients(Message& _inMsg, Message& _outMsg)
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



