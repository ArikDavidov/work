#include "Controller.h"
#include "SafeQueue.h"

#include <iostream>
#include <assert.h>

namespace smartcampus
{


Controller::Controller(AgentData* _agentData, ISubscriber* _hub)
: Agent(_agentData, _hub)
{
}

Controller::~Controller()
{
    pthread_cancel(m_thread);

    int err = pthread_join(m_thread, 0);
    if (0 != err)
    {
        errno = err;
        perror("Controller::~Controller: pthread_join");
    }
}

void Controller::Start()
{
    int err;
    if (0 != (err = pthread_create(&m_thread, 0, &Run, (void*)this)))
    {
        errno = err;
        perror("pthread_create");
    }
}

void* Controller::Run(void* _context)
{
    assert(_context);   //TODO throw error
    std::cout << "Controller::Run" << std::endl;

    Controller* pThis = (Controller*)_context;
    
    while (true)
    {
        pThis->DoOnEvent(pThis->m_eventQueue.Pop());
    }

    return 0;
}

void Controller::OnEvent(std::tr1::shared_ptr<Event> _event)
{
    m_eventQueue.Push(_event);
}

void Controller::DoOnEvent(std::tr1::shared_ptr<Event> _event)
{
    std::cout << "Got Event: " << _event->Topic() << std::endl;
}


}  // namespace smartcampus


