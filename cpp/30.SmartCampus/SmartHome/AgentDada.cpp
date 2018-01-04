#include "AgentData.h"

#include <iomanip>      // std::setw
#include <iostream>
#include <string>
#include <assert.h>

namespace smartcampus
{


std::ostream& operator<<(std::ostream& _os, const AgentData& _data)
{
	_os << std::setw(12) << std::left << _data.Id()
		<< "|" << std::setw(32) << std::left << _data.Type()
		<< "|" << std::setw(16) << std::left << _data.Floor()
		<< "|" << std::setw(12) << std::left << _data.Room()
		<< "|" << std::setw(12) << std::left << _data.Log()
		<< "|" << std::setw(12) << std::left << _data.Config();

	return _os;
}



AgentData::AgentData(const std::string& _id, const std::string& _type,
                     const std::string& _floor, const std::string&  _room,
                     const std::string& _log, const std::string& _config)
: m_id(_id)
, m_type(_type)
, m_floor(_floor)
, m_room(_room)
, m_log(_log)
, m_config(_config)
{
}

AgentData::~AgentData()
{
}





}  // namespace smartcampus


