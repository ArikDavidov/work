#include "ConfigParser.h"
#include "AgentData.h"

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>    // std::runtime_error
#include <sstream>      // std::istringstream


const std::string ConfigParser::s_whiteSpace(" \t\n\r");


ConfigParser::ConfigParser()
: m_lineNum(1)
{
    m_configs = new std::multimap<std::string, AgentData*>;
}

ConfigParser::~ConfigParser()
{
    delete m_configs;
}

AgentData* ConfigParser::GetNext()
{
    if (m_it == m_configs->end())
    {
        return 0;
    }

    AgentData* ret = m_it->second;
    ++m_it;

    return ret;
}

void ConfigParser::Parse(const std::string& _path)
{
    std::ifstream infile(_path.c_str());
    if(!infile)
    {  
        std::cerr << "Config file opening failed\n";
        return;
    }

    for(;!infile.fail();)
    {
        try {
            ParseID(infile);
        }
        catch(std::exception const& e) {
            break;
        }
        try {
            ParseConfigs(infile);
        }
        catch(std::exception const& e) {
            std::cerr << "Exception: Line " << m_lineNum
                      << ": " << e.what() << std::endl;
            delete m_data;
        }
    }
    
    m_it = m_configs->begin();
}

void ConfigParser::ParseID(std::ifstream& _infile)
{
    std::string line;
    for (;; ++m_lineNum)
    {
        std::getline(_infile, line);
        if (_infile.fail())
        {
            throw std::runtime_error("eof");
        }
        if (line == "") // Skip blank line
        {
            continue;
        }
        
        m_data = new AgentData;

        try {
            m_data->m_id = GetID(line);
            ++m_lineNum;
            break;
        }
        catch(std::exception const& e) {
            std::cerr << "Exception: Line " << m_lineNum 
                      << ": invalid ID" << std::endl;
            delete m_data;
        }
    }
}

std::string ConfigParser::GetID(const std::string& _line)
{
    std::string str = Trim(_line);
    str = StripBrakets(str);
    str = Trim(str);
    
    return str;
}

std::string ConfigParser::Trim(const std::string& _str)
{
    size_t first = _str.find_first_not_of(s_whiteSpace);
    if (std::string::npos == first)
    {
        throw std::runtime_error("");
    }
    
    size_t last = _str.find_last_not_of(s_whiteSpace);
    
    return _str.substr(first, last - first + 1);
}

std::string ConfigParser::StripBrakets(const std::string& _str)
{
    size_t first = _str.find_first_of("[");
    if (std::string::npos == first)
    {
        throw std::runtime_error("");
    }

    size_t last = _str.find_last_of("]");
    if (std::string::npos == last)
    {
        throw std::runtime_error("");
    }

    return _str.substr(first + 1, last - first -1);
}

void ConfigParser::ParseConfigs(std::ifstream& _infile)
{
    std::string line;
    for (;; ++m_lineNum)
    {
        std::getline(_infile, line);
        if (_infile.fail())
        {
            return;
        }
        if (line == "")
        {
            break;
        }

        FillField(line);   
    }

    if (m_data->m_type == "" || m_data->m_floor == "" || m_data->m_room == "")
    {
        throw std::runtime_error
              ("not enough configs to create agent " + m_data->m_id);
    }
    
    std::cout << "AgentData: " << m_data << std::endl;
    
    m_configs->insert(std::pair<std::string, AgentData*>(m_data->m_type, m_data));
}


void ConfigParser::FillField(const std::string& _line)
{
    Pair_t pair = GetPair(_line);

    if (pair.first == "type" && m_data->m_type == "")
    {
        m_data->m_type = pair.second;
    }    
    else if (pair.first == "floor" && m_data->m_floor == "")
    {
        m_data->m_floor = pair.second;
    }
    else if (pair.first == "room" && m_data->m_room == "")
    {
        m_data->m_room = pair.second;
    }
    else if (pair.first == "config" && m_data->m_config == "")
    {
        m_data->m_config = pair.second;
    }
    else if (pair.first == "log" && m_data->m_log == "")
    {
        m_data->m_log = pair.second;
    }
    else
    {
        throw std::runtime_error
              ("Illegal or duplicate field: \"" +
               pair.first + "\"");
    }
}

ConfigParser::Pair_t ConfigParser::GetPair(const std::string& _line)
{
    // chek if there is more than one '='
    if (_line.find('=') != _line.rfind('='))
    {
        throw std::runtime_error
              ("Not according to \"key = value\" format");
    }

    std::string key, value;
    std::istringstream iss(_line);
    
    getline(iss, key, '=');
    getline(iss, value);

    if (key == "" || value == "")
    {
        throw std::runtime_error
              ("Not according to \"key = value\" format");
    }
    
    return Pair_t(Trim(key), Trim(value));
}
    

 
