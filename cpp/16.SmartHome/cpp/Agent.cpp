#include "Agent.h"
#include "ISubscriber.h"
#include "AgentData.h"
#include "EventFilter.h"

#include <iostream>
#include <string>


Agent::Agent(AgentData* _agentData, ISubscriber* _hub)
: m_agentData(_agentData)
{
	this->Subscribe(_hub);
}

Agent::~Agent()
{
    delete m_agentData;
}

void Agent::Subscribe(ISubscriber* _subscriber, EventFilter* _eventFilter)
{
    m_hub = _subscriber;
}

void Agent::Publish(std::tr1::shared_ptr<Event> _event)
{
    m_hub->OnEvent(_event);
}


std::ostream& operator<<(std::ostream& _os, Agent* _agent)
{
	_os << _agent->m_agentData;

	return _os;
}



