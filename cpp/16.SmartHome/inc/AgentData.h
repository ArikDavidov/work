#ifndef __AGENT_DATA_H__
#define __AGENT_DATA_H__

#include <string>
#include <iostream>


class AgentData
{
    friend class ConfigParser;
public:
    explicit AgentData();
    virtual ~AgentData();

    const std::string& Id() const;
    const std::string& Type() const;
    const std::string& Room() const;
    const std::string& Floor() const;
    const std::string& Config() const;
    const std::string& Log() const;

    friend std::ostream& operator<<(std::ostream& _os, AgentData* _data);

private:
    AgentData(const AgentData&);
    AgentData& operator=(const AgentData&);

private:
	std::string m_id;
	std::string m_type;
	std::string m_floor;
	std::string m_room;
	std::string m_config;
	std::string m_log;
};


inline const std::string& AgentData::Id() const
{
    return m_id;
}
inline const std::string& AgentData::Type() const
{
    return m_type;
}
inline const std::string& AgentData::Room() const
{
    return m_room;
}
inline const std::string& AgentData::Floor() const
{
    return m_floor;
}
inline const std::string& AgentData::Config() const
{
    return m_config;
}
inline const std::string& AgentData::Log() const
{
    return m_log;
}

	
//std::ostream& operator<<(std::ostream& _os, AgentData* _data);


#endif	// __AGENT_DATA_H__



