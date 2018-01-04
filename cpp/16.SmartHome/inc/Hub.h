#ifndef __HUB_H__
#define __HUB_H__

#include "IPublisher.h"
#include "ISubscriber.h"
#include "SafeQueue.h"

#include <string>
#include <map>

class Event;
class EventFilter;


class Hub : public ISubscriber, public IPublisher
{
public:
    typedef std::multimap<std::string, ISubscriber*>::iterator iter_t;
    
    explicit Hub();
    virtual ~Hub();
    void     Start();
    
    virtual void Subscribe(ISubscriber* _subscriber, EventFilter* _eventFilter = 0);
//    virtual void Unsubscribe(ISubscriber* _subscriber, EventFilter* _eventFilter = 0) = 0;
    virtual void Publish(std::tr1::shared_ptr<Event> _event);

    virtual void OnEvent(std::tr1::shared_ptr<Event> _event);    

private: 
    Hub(const Hub&);
    Hub& operator=(const Hub&);

    static void* Run(void* _context);

private:
    std::multimap<std::string, ISubscriber*> m_controlers;
    SafeQueue<std::tr1::shared_ptr<Event> >  m_eventQueue;
    pthread_t                                m_thread;
};


#endif // __HUB_H__


