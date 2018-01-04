#ifndef __I_SUBSCRIBER_H__
#define __I_SUBSCRIBER_H__

#include "Event.h"


class ISubscriber
{
public:
	virtual ~ISubscriber();
    
    virtual void OnEvent(std::tr1::shared_ptr<Event> _event) = 0;
};


#endif // __I_SUBSCRIBER_H__


