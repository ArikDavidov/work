#ifndef __IPUBLISHER_H__
#define __IPUBLISHER_H__

#include "ISubscriber.h"
#include "Event.h"
#include "EventFilter.h"

#include <tr1/memory>

namespace smartcampus
{


class IPublisher
{
public:
	virtual ~IPublisher();

    virtual void Subscribe(std::tr1::shared_ptr<ISubscriber> _subscriber,
                           std::tr1::shared_ptr<EventFilter> _eventFilter) = 0;
protected:
    virtual void Publish(std::tr1::shared_ptr<Event> _event) = 0;
};




inline IPublisher::~IPublisher()
{
}



}  // namespace smartcampus

#endif // __IPUBLISHER_H__


