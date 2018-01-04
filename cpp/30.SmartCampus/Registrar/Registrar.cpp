#include "Registrar.h"
#include "DataBase.h"
#include "Util.h"       // Itoa

namespace smartcampus
{

const std::string Registrar::DB_NAME = "Registrar";
const std::string Registrar::TABLE_NAME = "SectionRegister";
const std::string Registrar::TABLE_COLUMNS = 
                    "SectionName, Address, SubsPort, EvtsPort";
const std::string Registrar::TABLE_PARAMETERS =
                    "SectionRegisterId INT PRIMARY KEY AUTO_INCREMENT,\
                        SectionName VARCHAR(255),\
                        Address VARCHAR(16),\
                        SubsPort INT,\
                        EvtsPort INT";

Registrar::Registrar(uint16_t _port)
: m_port(_port)
, m_db(new DataBase(DB_NAME))
{
    m_db->CreateTable(TABLE_NAME, TABLE_PARAMETERS);
}

Registrar::~Registrar()
{
}

void Registrar::RegisterSection(const std::string& _sectionName)
{
    m_db->InsertUniqueRecord(TABLE_NAME, TABLE_COLUMNS, _sectionName);
}

void Registrar::UnregisterSection(const std::string& _sectionName)
{
    m_db->RemoveRecord(TABLE_NAME, "SectionName", _sectionName);
}



}  // namespace smartcampus



