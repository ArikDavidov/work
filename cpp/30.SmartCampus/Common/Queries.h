#ifndef __QUERIES_H__
#define __QUERIES_H__

#include <tr1/memory>
#include "mysql_connection.h"

#include <cppconn/resultset.h>

namespace smartcampus
{

namespace queries
{




std::tr1::shared_ptr<sql::ResultSet>
    GetRecords(std::tr1::shared_ptr<sql::Statement> _stmt);

std::tr1::shared_ptr<sql::ResultSet>
	GetAgentsRecords(std::tr1::shared_ptr<sql::Statement> _stmt);







}   // namespace queries

}   // namespace smartcampus

#endif // __QUERIES_H__




