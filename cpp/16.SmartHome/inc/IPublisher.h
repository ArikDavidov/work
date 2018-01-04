#ifndef __IPUBLISHER_H__
#define __IPUBLISHER_H__

#include "Event.h"

class ISubscriber;
class EventFilter;



class IPublisher
{
public:
	virtual ~IPublisher();

    virtual void Subscribe(ISubscriber* _subscriber, EventFilter* _eventFilter = 0) = 0;
//    virtual void Unsubscribe(ISubscriber* _subscriber, EventFilter* _eventFilter = 0) = 0;
    virtual void Publish(std::tr1::shared_ptr<Event> _event) = 0;
};


#endif // __IPUBLISHER_H__


