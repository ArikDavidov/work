#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

#include <string>
//#include <iostream>

namespace smartcampus
{



class AgentData //: public uncopyable
{
public:
    explicit AgentData(const std::string& m_id, const std::string& m_type,
                       const std::string& m_floor, const std::string&  m_room,
                       const std::string& m_log, const std::string& m_config);
    virtual ~AgentData();

    const std::string& Id() const;
    const std::string& Type() const;
    const std::string& Floor() const;
    const std::string& Room() const;
    const std::string& Log() const;
    const std::string& Config() const;


private:
//    AgentData(const AgentData&);
//    AgentData& operator=(const AgentData&);

private:
	std::string m_id;
	std::string m_type;
	std::string m_floor;
	std::string m_room;
	std::string m_log;
	std::string m_config;
};


std::ostream& operator<<(std::ostream& _os, const AgentData& _data);


inline const std::string& AgentData::Id() const
{
    return m_id;
}
inline const std::string& AgentData::Type() const
{
    return m_type;
}
inline const std::string& AgentData::Floor() const
{
    return m_floor;
}
inline const std::string& AgentData::Room() const
{
    return m_room;
}
inline const std::string& AgentData::Log() const
{
    return m_log;
}
inline const std::string& AgentData::Config() const
{
    return m_config;
}

	

}  // namespace smartcampus

#endif	// __AGENT_DATA_H__



