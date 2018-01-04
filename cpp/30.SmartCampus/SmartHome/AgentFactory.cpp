#include "AgentFactory.h"
#include "ISubscriber.h"
#include "AgentData.h"
#include "SmartHomeAPI.h"

#include <dlfcn.h>
#include <iostream>

namespace smartcampus
{


AgentFactory::AgentFactory(std::tr1::shared_ptr<IHub> _hub)
: m_hub(_hub)
, m_agents(new std::map<std::string, std::tr1::shared_ptr<Agent> >)
{
    //std::cout << "AgentFactory::CTOR" << std::endl;
}

//std::cout << "AgentFactory::DTOR" << std::endl;
// std::map<std::string, Agent*>::iterator it = m_agents->begin();
// for (; it != m_agents->end(); ++it)
// {
//     delete it->second;
// }
// delete m_agents;
AgentFactory::~AgentFactory()
{
}

void AgentFactory::CreateAgent(void* _handle,
                               std::tr1::shared_ptr<AgentData> _agentData)
{
    if (m_agents->count(_agentData->Id()))
    {
        std::cout << "Error: agent with id " << _agentData->Id()
                  << " already exist" << std::endl;
        return;
    }
    
    CreateObjFunc Create = (CreateObjFunc)dlsym(_handle, "CreateObj");
    std::tr1::shared_ptr<Agent> agent(Create(_agentData, m_hub));
    
    m_agents->insert(std::make_pair(_agentData->Id(), agent));
    
    std::tr1::shared_ptr<Controller> controller =
        std::tr1::dynamic_pointer_cast<Controller>(agent);
    if (controller)
    {
        controller->Start();
    }
}



}  // namespace smartcampus


