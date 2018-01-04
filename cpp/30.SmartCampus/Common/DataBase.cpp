#include "DataBase.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>


namespace smartcampus
{

const std::string DataBase::PORT = "3306";
const std::string DataBase::USER = "root";
const std::string DataBase::PASSWORD = "student";


DataBase::DataBase(const std::string& _dbName)
{
    sql::Driver* driver = get_driver_instance();
    m_con.reset(driver->connect("tcp://127.0.0.1:" + PORT,
                                    USER, PASSWORD));
    m_con->setSchema(_dbName);
}

DataBase::~DataBase()
{
}

void DataBase::CreateTable(const std::string& _tableName,
                           const std::string& _tableParameters)
{
    std::tr1::shared_ptr<sql::Statement> stmt(m_con->createStatement());
    
    stmt->execute("DROP TABLE IF EXISTS " + _tableName);
    stmt->execute("CREATE TABLE " + _tableName + "(" + _tableParameters + ")");
}

void DataBase::InsertUniqueRecord(const std::string& _tableName,
                                  const std::string& _columnNames, 
                                  const std::string& _name)
{
    std::tr1::shared_ptr<sql::Statement> stmt(m_con->createStatement());
    // check if already registerd
    stmt->execute("INSERT INTO " + _tableName + "(" + _columnNames + ")"
                  + " VALUES('" + _name + "', '127.0.0.1', 2222, 3333)");
}

void DataBase::RemoveRecord(const std::string& _tableName, 
                            const std::string& _columnName,
                            const std::string& _value)
{    
    std::tr1::shared_ptr<sql::Statement> stmt(m_con->createStatement());

    std::tr1::shared_ptr<sql::ResultSet> res(stmt->executeQuery
                        ("SELECT " + _columnName + 
                        " FROM " + _tableName + 
                        " WHERE " + _columnName + " = '" + _value + "'"));
    if (!res->next())
    {
        throw std::runtime_error("Section not found");
    }
    
    stmt->execute("DELETE FROM " + _tableName +
                 " WHERE " + _columnName + " = '" + _value + "'");
}



}  // namespace smartcampus


