#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <tr1/memory>
#include <vector>

namespace smartcampus
{

class DataBase;
class AgentData;


class Config
{
public:
    explicit Config(const std::string& _sectionName);
    ~Config();
    
    std::tr1::shared_ptr<std::vector<std::tr1::shared_ptr<AgentData> > > GetAgetsData();

private:
    std::tr1::shared_ptr<DataBase> m_db;
};

    
    
    
    
}  // namespace smartcampus

#endif // __CONFIG_H__


