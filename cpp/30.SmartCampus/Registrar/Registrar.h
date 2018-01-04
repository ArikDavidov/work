#ifndef __REGISTRAR_H__
#define __REGISTRAR_H__

// #include "DataBase.h"

#include <stdint.h>		// uint16_t
#include <tr1/memory>
#include <string>

namespace smartcampus
{

class DataBase;


class Registrar // : public uncopyable
{
    static const std::string DB_NAME;
    static const std::string TABLE_NAME;
    static const std::string TABLE_COLUMNS;
    static const std::string TABLE_PARAMETERS;
public:
    explicit Registrar(uint16_t _port);
    ~Registrar();
    
    void RegisterSection(const std::string& _sectionName);
    void UnregisterSection(const std::string& _sectionName);
    
//    SectionDetails { m_name, m_address, m_subsPort, m_evtsPort }
//    SectionDetails Get();
//    List();
//    ListFull();
//    Tellme();
    

private:
    uint16_t m_port;
    std::tr1::shared_ptr<DataBase> m_db;
};


}  // namespace smartcampus

#endif // __REGISTRAR_H__




