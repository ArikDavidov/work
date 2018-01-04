#include "SmartHome.h"
#include "Hub.h"
#include "AgentFactory.h"
#include "ConfigParser.h"
#include "Loader.h"
#include "AgentData.h"

#include <string>
#include <iostream>


SmartHome::SmartHome(const std::string& _confPath)
: m_confPath(_confPath)
{
    m_hub          = new Hub;
    m_loader       = new Loader;
    m_agentFactory = new AgentFactory(m_hub);
}

SmartHome::~SmartHome()
{
    delete m_agentFactory;
    delete m_loader;
    delete m_hub;
}

void SmartHome::Init()
{
    m_hub->Start();
    m_loader->ObtainSupportedTypes();
    
    ConfigParser parser;
    parser.Parse(m_confPath);

    AgentData* agentData;
    void* handle;
    while (0 != (agentData = parser.GetNext()))
    {
        handle = m_loader->GetHandle(agentData->Type());
        m_agentFactory->CreateAgent(handle, agentData);
    }
}




