#ifndef __DEMUX_H__
#define __DEMUX_H__

#include "Selector.h"
#include <vector>
#include <tr1/memory>

namespace net
{

class Socket;



class DeMux
{
public:
    explicit DeMux();
    ~DeMux();
    
    void Add(std::tr1::shared_ptr<Socket> _sock);
    void WaitForActivity(std::vector<std::tr1::shared_ptr<Socket> >& _readySockets);

private:
    Selector m_selector;
    std::tr1::shared_ptr<ListeningSocket> m_listeningSock;////////////////???????????
};



    
    
}  // namespace net

#endif // __DEMUX_H__


