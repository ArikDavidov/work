#include "Sensor.h"
#include "Controller.h"
#include "AgentData.h"
#include "Hub.h"

#include <unistd.h>			// usleep
#include <iostream>
//using namespace std;
// typedef std::tr1::shared_ptr<Event> spEvent_t;

int main()
{
	AgentData* sensorData = new AgentData;
	sensorData->m_id     = "1";
	sensorData->m_type   = "2";
	sensorData->m_room   = "3";
	sensorData->m_floor  = "4";
	sensorData->m_config = "5";
	sensorData->m_log    = "6";

	AgentData* controllerData = new AgentData;
	controllerData->m_id     = "1";
	controllerData->m_type   = "2";
	controllerData->m_room   = "3";
	controllerData->m_floor  = "4";
	controllerData->m_config = "5";
	controllerData->m_log    = "6";

	Hub* hub = new Hub;
	hub->Start();
	Agent* sensor = new Sensor(sensorData);
	Controller* controller = new Controller(controllerData);
	controller->Start();
	
	sensor->Subscribe(hub);

	EventFilter* eventFilter = new EventFilter;
	eventFilter->m_topic   = "CATS";
	eventFilter->m_floor  = "3";
	eventFilter->m_room   = "42";

	controller->Subscribe(hub);
	hub->Subscribe(controller, eventFilter);


	Event::sp event(new Event("CATS", "3", "42"));
	hub->OnEvent(event);
	
	usleep(1000000);
	std::cout << "sleep" << std::endl;
	

	delete hub;
	delete sensor;
	delete controller;

	return 0;
}



	//controller->Start();

	
