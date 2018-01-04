#include "Queries.h"

#include <cppconn/statement.h>
//#include <cppconn/resultset.h>//////
//#include <cppconn/driver.h>
//#include <cppconn/exception.h>

namespace smartcampus
{

namespace queries
{




std::tr1::shared_ptr<sql::ResultSet> GetRecords(std::tr1::shared_ptr<sql::Statement> _stmt)
{
    std::tr1::shared_ptr<sql::ResultSet> res(_stmt->executeQuery
        ("SELECT DeviceId\
            , DeviceTypeName AS DeviceType\
            , CASE WHEN r.LocationId IS NOT NULL THEN ff.LocationName ELSE f.LocationName END AS Floor\
            , r.LocationName AS Room\
            , LogName AS Log\
            , Configuration\
        FROM Agent a\
        JOIN DeviceType d ON d.DeviceTypeId = a.DeviceTypeId\
        JOIN Log l ON l.LogId =  a.LogId\
        LEFT JOIN Location r ON r.LocationId = a.LocationId AND r.PID IS NOT NULL\
        LEFT JOIN Location f ON f.LocationId = a.LocationId AND f.PID IS NULL\
        LEFT JOIN Location ff ON r.PID = ff.LocationId"));

    return res;
}


std::tr1::shared_ptr<sql::ResultSet> GetAgentsRecords(std::tr1::shared_ptr<sql::Statement> _stmt)
{
    std::tr1::shared_ptr<sql::ResultSet> res(_stmt->executeQuery
        ("SELECT DeviceId\
            , DeviceTypeName AS DeviceType\
            , f.LocationName AS Floor\
            , r.LocationName AS Room\
            , LogName AS Log\
            , Configuration\
        FROM Agent a\
        JOIN DeviceType d ON d.DeviceTypeId = a.DeviceTypeId\
        JOIN Log l ON l.LogId =  a.LogId\
        JOIN Location r ON r.LocationId = a.LocationId\
        JOIN Location f ON f.LocationId = r.PID"));

    return res;
}


}   // namespace queries

}   // namespace smartcampus


