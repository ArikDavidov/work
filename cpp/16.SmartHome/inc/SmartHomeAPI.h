#ifndef __SMART_HOME_API_H__
#define __SMART_HOME_API_H__

#include "Hub.h"
#include "Agent.h"
#include "Sensor.h"
#include "Controller.h"
#include "AgentData.h"
#include "EventFilter.h"

#include <string>


extern "C" Agent* CreateObj(AgentData* _agentData, ISubscriber* _hub);
extern "C" std::string GetNextSupportedType();


#endif	// __SMART_HOME_API_H__




