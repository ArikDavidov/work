#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Agent.h"
#include "ISubscriber.h"
#include "SafeQueue.h"
#include "Event.h"

#include <pthread.h>


class Controller : public Agent, public ISubscriber
{
public:
	explicit Controller(AgentData* _agentData, ISubscriber* _hub);
	virtual ~Controller();

    virtual void OnEvent(std::tr1::shared_ptr<Event> _event);
    // virtual void Subscribe(ISubscriber* _subscriber, EventFilter* _eventFilter = 0);
    // virtual void Publish(Event::sp _event);
    void Start();

private:
    Controller(const Controller&);
    Controller& operator=(const Controller&);

    static  void* Run(void* _context);
    virtual void  DoOnEvent(std::tr1::shared_ptr<Event> _event);

private:
    SafeQueue<std::tr1::shared_ptr<Event> > m_eventQueue;
    pthread_t                               m_thread;
};


#endif // __CONTROLLER_H__

