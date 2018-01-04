#include <iostream>
#include <tr1/memory>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>


int main()
{
    sql::Driver* driver = get_driver_instance();

    std::tr1::shared_ptr<sql::Connection> con(driver->connect
            ("tcp://127.0.0.1:3306/SmartCammpus", "root", "student"));

    std::tr1::shared_ptr<sql::Statement> stmt(con->createStatement());

    for (int i = 0; i < 2; ++i)
    {
        stmt->execute("INSERT INTO Location(LocationName, PID) VALUES('Building_G', NULL);");

        std::tr1::shared_ptr<sql::ResultSet>
                        res(stmt->executeQuery("SELECT * FROM Location"));

        while (res->next())
        {
            std::cout << "LocationId: " << res->getInt("LocationId")
                      << " LocationName: " << res->getString("LocationName")
                      << " PID: " << res->getString("PID")
                      << std::endl;
        }
    }

    return 0;
}


