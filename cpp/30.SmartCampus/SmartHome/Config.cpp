#include "Config.h"
#include "DataBase.h"
#include "AgentData.h"
#include "Queries.h"
#include <iostream>//////

#include <cppconn/resultset.h>////

namespace smartcampus
{


Config::Config(const std::string& _sectionName)
: m_db(new DataBase(_sectionName))
{
}

Config::~Config()
{
}


std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<AgentData> > >
Config::GetAgetsData()
{
	std::string id, type, floor, room, log, config;
    std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<AgentData> > >
            agentsData(new std::vector<std::tr1::shared_ptr<AgentData> >);            
    std::tr1::shared_ptr<AgentData> data;
    
    std::tr1::shared_ptr<sql::ResultSet> res = 
                    queries::GetAgentsRecords(m_db->GetNativeStatement());

    while (res->next())
    {
        id = res->getString("DeviceId");
        type = res->getString("DeviceType");
        floor = res->getString("Floor");
        room = res->getString("Room");
        log = res->getString("Log");        
        config = res->getString("Configuration");
    
        data.reset(new AgentData(id, type, floor, room, log, config));

        agentsData->push_back(data);
    }


    return agentsData;
}






   
   
}  // namespace smartcampus



