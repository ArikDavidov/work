#include "Hub.h"
#include "Event.h"
#include "EventFilter.h"
#include "Controller.h"

#include <assert.h>

namespace smartcampus
{


Hub::Hub()
{
    std::cout << "Hub::CTOR" << std::endl;
}

Hub::~Hub()
{
    std::cout << "Hub::DTOR" << std::endl;

    pthread_cancel(m_thread);

    int err = pthread_join(m_thread, 0);
    if (0 != err)
    {
        errno = err;
        perror("pthread_join");
    }
}

void Hub::Start()
{
    int err;
    if (0 != (err = pthread_create(&m_thread, 0, &Run, (void*)this)))
    {
        errno = err;
        perror("pthread_create");
    }
}

void* Hub::Run(void* _context)
{
    assert(_context);
    
    std::cout << "Hub::Run" << std::endl;

    Hub* pThis = (Hub*)_context;
    std::tr1::shared_ptr<Event> event;
    
    while (true)
    {
        event = pThis->m_eventQueue.Pop();
        pThis->Publish(event);
    }

    return 0;
}

void Hub::Subscribe(std::tr1::shared_ptr<ISubscriber> _subscriber,
                    std::tr1::shared_ptr<EventFilter> _eventFilter)
{
    std::string topic = _eventFilter ? _eventFilter->Topic() : "";
    m_controlers->insert(std::pair<std::string, 
                        ISubscriber*>(topic, _subscriber));
    
    std::cout << "Hub: Subscriber subscribed to topic: " 
              << _eventFilter->Topic() << std::endl;
}    

void Hub::Unsubscribe(ISubscriber* _subscriber, EventFilter* _eventFilter)
{
    std::string topic = _eventFilter ? _eventFilter->Topic() : "";
    std::multimap<std::string, ISubscriber*>::iterator it = m_controlers.find(topic);
    m_controlers.remov(std::pair<std::string, 
                        ISubscriber*>(topic, _subscriber));
       
    std::cout << "Hub: Subscriber Unsubscribed" << std::endl;
}

Hub::iter_t Hub::FindSubdcdription(EventFilter* _eventFilter, ISubscriber* _subscriber)
{ 
    pair<iter_t, iter_t> range = m_observers.equal_range(_type);
    for (iter_t it = range.first; it != range.second; ++it)
    {
        if (it->second == _observer)
        {
            return it;
        }
    }
    
    return m_observers.end();
}

void Hub::Publish(std::tr1::shared_ptr<Event> _event)
{
    std::pair<iter_t, iter_t> range = m_controlers.equal_range(_event->Topic());
    for (iter_t it = range.first; it != range.second; ++it)
    {
        it->second->OnEvent(_event);
    }
}

void Hub::OnEvent(std::tr1::shared_ptr<Event> _event)
{
    m_eventQueue.Push(_event);
}


}  // namespace smartcampus



