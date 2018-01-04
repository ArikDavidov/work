#include "Agent.h"
//#include "ISubscriber.h"
//#include "AgentData.h"
#include "EventFilter.h"
#include "IHub.h"
#include "Event.h"

#include <iostream>
#include <string>

namespace smartcampus
{


Agent::Agent(std::tr1::shared_ptr<AgentData> _agentData,
             std::tr1::shared_ptr<IHub> _hub)
: m_agentData(_agentData)
, m_hub(_hub)
{
}

Agent::~Agent()
{
}

void Agent::PublishEvent(std::tr1::shared_ptr<Event> _event)
{
    m_hub->OnEvent(_event);
}



}  // namespace smartcampus


