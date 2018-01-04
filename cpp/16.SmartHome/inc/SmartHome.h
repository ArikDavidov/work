#ifndef __SMART_HOME_H__
#define __SMART_HOME_H__

#include <string>

class Hub;
class Loader;
class AgentFactory;


class SmartHome
{
public:
    SmartHome(const std::string& _confPath);
    virtual ~SmartHome();
    
    void Init();

private:
    SmartHome(const SmartHome&);
    SmartHome& operator=(const SmartHome&);

private: 
    std::string   m_confPath;
    Hub*          m_hub;
    AgentFactory* m_agentFactory;
    Loader*       m_loader;
};


#endif  // __SMART_HOME_H__


