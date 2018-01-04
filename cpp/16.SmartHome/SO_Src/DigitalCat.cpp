#include "DigitalCat.h"
#include "SmartHomeAPI.h"
#include "Agent.h"

#include <string>


const std::string DigitalCatFactory::s_supportedTypes[] = {"DigitalCat800", "DigitalCat900"};
unsigned DigitalCatFactory::s_posNextGet = 0;


Agent* CreateObj(AgentData* _agentData, ISubscriber* _hub)
{
    return DigitalCatFactory::CreateDigitalCat(_agentData, _hub);
}

std::string GetNextSupportedType()
{
	return DigitalCatFactory::GetNextSupported();
}

Agent* DigitalCatFactory::CreateDigitalCat(AgentData* _agentData, ISubscriber* _hub)
{
    Agent* ptrDigitalCat = 0;
    if (_agentData->Type() == "DigitalCat800"){
        ptrDigitalCat = new DigitalCat800(_agentData, _hub);
        ((DigitalCat800*)ptrDigitalCat)->Start();
    }
    if (_agentData->Type() == "DigitalCat900")
        ptrDigitalCat = new DigitalCat900(_agentData, _hub);
    return ptrDigitalCat;
}

std::string DigitalCatFactory::GetNextSupported()
{
	if (s_posNextGet >= sizeof(s_supportedTypes)/sizeof(s_supportedTypes[0]))
	{
		return "";
	}

	return s_supportedTypes[s_posNextGet++];
}






