#ifndef __HUB_H__
#define __HUB_H__

// #include "IPublisher.h"
// #include "ISubscriber.h"
#include "IHub.h"
#include "SafeQueue.h"

#include <string>
#include <map>

namespace smartcampus
{

class Event;
class EventFilter;


class Hub : public IHub //public Runnable //, private uncopyable
{
public:
    // typedef std::multimap<std::string, ISubscriber*>::iterator iter_t;
    
    explicit Hub();
    virtual ~Hub();
    void Start();
    
    virtual void Subscribe(std::tr1::shared_ptr<ISubscriber> _subscriber,
                           std::tr1::shared_ptr<EventFilter> _eventFilter);
//    virtual void Unsubscribe(ISubscriber* _subscriber, EventFilter* _eventFilter = 0);

    virtual void OnEvent(std::tr1::shared_ptr<Event> _event);

private:
    virtual void Publish(std::tr1::shared_ptr<Event> _event);
    static void* Run(void* _context);
    
    std::tr1::shared_ptr<std::multimap
        <std::string, std::tr1::weak_ptr<ISubscriber> > > m_controlers;
    SafeQueue<std::tr1::shared_ptr<Event> >  m_eventQueue;
    pthread_t m_thread;
};



}   // namespace smartcampus

#endif // __HUB_H__


