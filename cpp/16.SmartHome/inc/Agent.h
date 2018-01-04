#ifndef __AGENT_H__
#define __AGENT_H__

#include "IPublisher.h"
#include "Event.h"
#include "AgentData.h"

class ISubscriber;
class EventFilter;


class Agent : public IPublisher
{
public:
    explicit Agent(AgentData* _agentData, ISubscriber* _hub);
    virtual ~Agent();

    virtual void Subscribe(ISubscriber* _subscriber, EventFilter* _eventFilter = 0);
    virtual void Publish(std::tr1::shared_ptr<Event> _event);
    
    const std::string& Id() const;
    const std::string& Type() const;
    const std::string& Room() const;
    const std::string& Floor() const;
    const std::string& Config() const;
    const std::string& Log() const;

    friend std::ostream& operator<<(std::ostream& _os, Agent* _agent);

private:
    Agent(const Agent&);
    Agent& operator=(const Agent&);

protected:
    ISubscriber* m_hub;
    AgentData* m_agentData;
};


inline const std::string& Agent::Id() const
{
    return m_agentData->Id();
}
inline const std::string& Agent::Type() const
{
    return m_agentData->Type();
}
inline const std::string& Agent::Room() const
{
    return m_agentData->Room();
}
inline const std::string& Agent::Floor() const
{
    return m_agentData->Floor();
}
inline const std::string& Agent::Config() const
{
    return m_agentData->Config();
}
inline const std::string& Agent::Log() const
{
    return m_agentData->Log();
}


#endif // __AGENT_H__



