#ifndef __AGENT_FACTORY_H__
#define __AGENT_FACTORY_H__

#include <map>
#include <string>
#include <tr1/memory>


namespace smartcampus
{

class Agent;
class AgentData;
class IHub;
class ISubscriber;


class AgentFactory
{
public:
    typedef Agent* (*CreateObjFunc)(AgentData*, ISubscriber*);///////////

    explicit AgentFactory(std::tr1::shared_ptr<IHub> _hub);
    virtual ~AgentFactory();
    
    void CreateAgent(void* _handle, std::tr1::shared_ptr<AgentData> _agentData);

private:
    std::tr1::shared_ptr<IHub> m_hub;
    std::tr1::shared_ptr<std::map
        <std::string, std::tr1::shared_ptr<Agent> > > m_agents;
};



}  // namespace smartcampus

#endif // __AGENT_FACTORY_H__

