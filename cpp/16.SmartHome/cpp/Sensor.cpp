#include "Sensor.h"
#include "AgentData.h"

#include <iostream>


Sensor::Sensor(AgentData* _agentData, ISubscriber* _hub)
: Agent(_agentData, _hub)
{
}

Sensor::~Sensor()
{
}


