#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <map>
#include <string>
#include <sstream>

class AgentData;


class ConfigParser
{
public:
    typedef std::pair<std::string, std::string> Pair_t;

    explicit ConfigParser();
    virtual ~ConfigParser();
    
    void       Parse(const std::string& _path);
    AgentData* GetNext();

protected:
    void        FillField(const std::string& _line);
    Pair_t      GetPair(const std::string& _line);
    std::string GetID(const std::string& _line);
    void        ParseConfigs(std::ifstream& _infile);
    void        ParseID(std::ifstream& _infile);
    std::string StripBrakets(const std::string& _str);
    std::string Trim(const std::string& _str);

private:
    ConfigParser(const ConfigParser&);
    ConfigParser & operator=(const ConfigParser&);

private:
    std::multimap<std::string, AgentData*>*          m_configs;
    std::multimap<std::string, AgentData*>::iterator m_it;
    unsigned                                         m_lineNum;
    AgentData*                                       m_data;

    static const std::string                         s_whiteSpace;
};


#endif  // __CONFIG_PARSER_H__

    // std::string Itoa(int _i);
// inline std::string ConfigParser::Itoa(int _i)
// {
//     std::ostringstream ss;
//     ss << _i;
//     return ss.str();
// }





