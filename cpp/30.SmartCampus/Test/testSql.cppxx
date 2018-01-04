#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


int main(void)
{
std::cout << std::endl;
std::cout << "Let's have MySQL count from 10 to 1..." << std::endl;

try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;
  sql::PreparedStatement *pstmt;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306/SmartCammpus", "root", "student");
  /* Connect to the MySQL test database */
  //con->setSchema("SmartCammpus");

    /* Creating a "simple" statement - "simple" = not a prepared statement */
    std::auto_ptr< sql::Statement > stmt(con->createStatement());

    /* Create a test table demonstrating the use of sql::Statement.execute() */
    // stmt->execute("USE " + database);
    // stmt->execute("DROP TABLE IF EXISTS test");
    // stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");

    sql.str("");
    sql << "INSERT INTO test(id, label) VALUES (";
    sql << test_data[i].id << ", '" << test_data[i].label << "')";
    stmt->execute(sql.str());

    "INSERT INTO Location(LocationName, PID) VALUES('Building_A', NULL);"


  /* '?' is the supported placeholder syntax */
  // pstmt = con->prepareStatement("INSERT INTO test(id) VALUES (?)");
  // for (int i = 1; i <= 2; i++) {
  //   pstmt->setInt(1, i);
  //   pstmt->executeUpdate();
  // }
  delete pstmt;

  /* Select in ascending order */
  pstmt = con->prepareStatement("SELECT id FROM test ORDER BY id ASC");
  res = pstmt->executeQuery();

  /* Fetch in reverse = descending order! */
  res->afterLast();
  while (res->previous())
    std::cout << "\t... MySQL counts: " << res->getInt("id") << std::endl;
  delete res;

  delete pstmt;
  delete con;

} catch (sql::SQLException &e) {
  std::cout << "# ERR: SQLException in " << __FILE__;
  std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
  std::cout << "# ERR: " << e.what();
  std::cout << " (MySQL error code: " << e.getErrorCode();
  std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
}

std::cout << std::endl;

return EXIT_SUCCESS;
}
