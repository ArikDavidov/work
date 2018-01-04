#ifndef __I_HUB_H__
#define __I_HUB_H__

#include "ISubscriber.h"
#include "IPublisher.h"

namespace smartcampus
{


class IHub : public IPublisher, public ISubscriber
{
public:
    virtual ~IHub();

    // virtual void Subscribe(std::tr1::shared_ptr<ISubscriber> _subscriber,
    //                        std::tr1::shared_ptr<EventFilter> _eventFilter) = 0;

    // virtual void OnEvent(std::tr1::shared_ptr<Event> _event) = 0;

protected:
    // virtual void Publish(std::tr1::shared_ptr<Event> _event) = 0;

};


inline IHub::~IHub()
{
}



}   // namespace smartcampus

#endif // __I_HUB_H__


