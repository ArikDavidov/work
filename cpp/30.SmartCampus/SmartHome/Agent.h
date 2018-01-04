#ifndef __AGENT_H__
#define __AGENT_H__

#include "AgentData.h"
//#include "IPublisher.h"
//#include "Event.h"
//#include "IHub.h"

#include <tr1/memory>

namespace smartcampus
{

class AgentData;
class IHub;
class Event;
class EventFilter;


class Agent // : public uncopyable
{
public:
    explicit Agent(std::tr1::shared_ptr<AgentData> _agentData,
                   std::tr1::shared_ptr<IHub> _hub);
    virtual ~Agent();

    virtual void PublishEvent(std::tr1::shared_ptr<Event> _event);
    
    
    std::ostream& Print(std::ostream& _os) const;
    
    const std::string& Id() const;
    const std::string& Type() const;
    const std::string& Room() const;
    const std::string& Floor() const;
    const std::string& Config() const;
    const std::string& Log() const;

protected:
    std::tr1::shared_ptr<AgentData> m_agentData;
    std::tr1::shared_ptr<IHub> m_hub;
};


inline std::ostream& operator<<(std::ostream& _os,
                         std::tr1::shared_ptr<Agent> _agent)
{
    _agent->Print(_os);
    return _os;
}

inline std::ostream& Agent::Print(std::ostream& _os) const
{
    _os << m_agentData;
    return _os;
}

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



}  // namespace smartcampus

#endif // __AGENT_H__


