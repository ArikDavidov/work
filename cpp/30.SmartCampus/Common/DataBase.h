#ifndef __DATA_BASE_H__
#define __DATA_BASE_H__

#include <string>
#include <tr1/memory>

#include "mysql_connection.h"
#include <cppconn/resultset.h>//////
#include <cppconn/statement.h>

namespace smartcampus
{

/////class sql::ResultSet;



class DataBase
{
    static const std::string PORT;
    static const std::string USER;
    static const std::string PASSWORD;
public:
    explicit DataBase(const std::string& _dbName);
    ~DataBase();
    
    void CreateTable(const std::string& _tableName,
                     const std::string& _tableParameters);
                     
    void InsertUniqueRecord(const std::string& _tableName,
                            const std::string& _columnNames, 
                            const std::string& _name);

    void RemoveRecord(const std::string& _tableName, 
                      const std::string& _columnName,
                      const std::string& _value);
//    void Insert();
//    void InsertUnic();

    std::tr1::shared_ptr<sql::Statement> GetNativeStatement() const;

private:
    std::tr1::shared_ptr<sql::Connection> m_con;
};

    
inline std::tr1::shared_ptr<sql::Statement> DataBase::GetNativeStatement() const
{
    std::tr1::shared_ptr<sql::Statement> stmt(m_con->createStatement());

    return stmt;
}



}  // namespace smartcampus

#endif // __DATA_BASE_H__



