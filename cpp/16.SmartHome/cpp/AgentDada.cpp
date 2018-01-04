#include "AgentData.h"

#include <iostream>
#include <string>
#include <assert.h>

AgentData::AgentData()
{
}

AgentData::~AgentData()
{
}

std::ostream& operator<<(std::ostream& _os, AgentData* _data)
{
	assert(_data);

	_os << _data->m_id    << "|" << _data->m_type << "|"
    	<< _data->m_floor << "|" << _data->m_room << "|"
        << _data->m_log   << "|" << _data->m_config;

	return _os;
}


