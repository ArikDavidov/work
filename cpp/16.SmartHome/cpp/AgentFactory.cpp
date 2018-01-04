#include "AgentFactory.h"
#include "ISubscriber.h"
#include "AgentData.h"
#include "SmartHomeAPI.h"

#include <dlfcn.h>
#include <iostream>


AgentFactory::AgentFactory(ISubscriber* _hub)
: m_hub(_hub)
{
    std::cout << "AgentFactory::CTOR" << std::endl;
    m_agents = new std::map<std::string, Agent*>;
}

AgentFactory::~AgentFactory()
{
    std::cout << "AgentFactory::DTOR" << std::endl;

    std::map<std::string, Agent*>::iterator it = m_agents->begin();
    for (; it != m_agents->end(); ++it)
    {
        delete it->second;
    }
    
    delete m_agents;
}

void AgentFactory::CreateAgent(void* _handle, AgentData* _agentData)
{
    if (m_agents->count(_agentData->Id()))
    {
        std::cout << "Error: agent with id " << _agentData->Id()
                  << " already exist" << std::endl;
        return;
    }
    
    CreateObjFunc Create = (CreateObjFunc)dlsym(_handle, "CreateObj");
    Agent* agent = Create(_agentData, m_hub);
    
    m_agents->insert(std::pair<std::string,
                     Agent*>(_agentData->Id(), agent));
    
    Controller* controller = dynamic_cast<Controller*>(agent);
    if (controller)
    {
        controller->Start();
    }
}




//    char *error;
//    if ((error = dlerror()) != 0)  {
//        std::cerr << error << std::endl;
//        throw;
//    }

