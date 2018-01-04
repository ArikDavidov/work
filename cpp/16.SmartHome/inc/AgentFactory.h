#ifndef __AGENT_FACTORY_H__
#define __AGENT_FACTORY_H__

#include <map>
#include <string>

class Agent;
class AgentData;
class ISubscriber;


class AgentFactory
{
public:
    typedef Agent* (*CreateObjFunc)(AgentData*, ISubscriber*);

    explicit AgentFactory(ISubscriber* _hub);
    virtual ~AgentFactory();
    
    void CreateAgent(void* _handle, AgentData* _agentData);

private:
    std::map<std::string, Agent*>* m_agents;
    ISubscriber*                   m_hub;
};



#endif // __AGENT_FACTORY_H__



