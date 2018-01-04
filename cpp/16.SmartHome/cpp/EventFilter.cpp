#include "EventFilter.h"
#include "Event.h"

#include <string>
#include <iostream>


EventFilter::EventFilter(std::string _topic, std::string _floor,
						 std::string _room)
: m_topic(_topic), m_floor(_floor), m_room(_room)
{
}

EventFilter::~EventFilter()
{
}

std::ostream& operator<<(std::ostream& _os, EventFilter* _filter)
{
	_os << _filter->m_topic << "|" << _filter->m_floor << "|"
    	<< _filter->m_room;

	return _os;
}

//EventFilter::EventFilter(Event::sp _event)
//: m_topic(_event._topic), m_floor(_event._floor),
//  m_room(_event._room)
//{
//    
//}

//bool EventFilter::operator<(EventFilter* _eventFilter)
//{
//    if(m_topic != _eventFilter->m_topic)
//    {
//        return m_topic < _eventFilter->m_topic;
//    }
//    if(m_floor != _eventFilter->m_floor)
//    {
//        return m_floor < _eventFilter->m_floor;
//    }
//    if(m_room != _eventFilter->m_room)
//    {
//        return m_room < _eventFilter->m_room;
//    }
//    
//    return false;
//}

//bool EventFilter::operator==(EventFilter* _eventFilter)
//{
//    if(m_topic != _eventFilter->m_topic)
//    {
//        return false;
//    }
//    if(m_floor != _eventFilter->m_floor)
//    {
//        return false;
//    }
//    if(m_room != _eventFilter->m_room)
//    {
//        return false;
//    }
//    
//    return true;
//}




