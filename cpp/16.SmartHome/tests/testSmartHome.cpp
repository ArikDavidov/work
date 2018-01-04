#include "SmartHome.h"
#include "Hub.h"
#include "ConfigParser.h"
#include "Loader.h"
#include "AgentData.h"
#include "AgentFactory.h"

#include <unistd.h>
#include <iostream>


int main()
{
    Hub* m_hub = new Hub;
    m_hub->Start();

    
    ConfigParser parser;
    parser.Parse("DummyPath");	// m_confPath

    Loader loader;
    loader.ObtainSupportedTypes();
    AgentFactory* m_agentFactory = new AgentFactory(m_hub);
    AgentData* agentData;
    void* handle;
    while (0 != (agentData = parser.GetNext()))
    {
        handle = loader.GetHandle(agentData->Type());
        m_agentFactory->CreateAgent(handle, agentData);
    }
    
    usleep(1000000);
    std::cout << "sleep" << std::endl;
    
    delete m_agentFactory;
    delete m_hub;
    
    return 0;
}


