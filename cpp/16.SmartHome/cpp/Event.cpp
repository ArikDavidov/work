#include "Event.h"

#include <string>
#include <iostream>


Event::Event(std::string _topic, std::string _floor, 
             std::string _room)
: m_topic(_topic), m_floor(_floor), m_room(_room)
{
//    std::cout << "Event::CTOR" << std::endl;
}

Event::~Event()
{
    std::cout << "Event::DTOR" << this << std::endl;
}


