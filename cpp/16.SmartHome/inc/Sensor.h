#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <iostream>

#include "Agent.h"

class AgentData;



class Sensor : public Agent
{
public:
    explicit Sensor(AgentData* _agentData, ISubscriber* _hub);
    virtual ~Sensor();
};


#endif  // __SENSOR_H__


