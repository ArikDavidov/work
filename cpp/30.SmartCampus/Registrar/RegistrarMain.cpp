#include "Registrar.h"

#include <cppconn/exception.h>
#include <cstdlib>               // abort, atoi
#include <iostream>

using namespace smartcampus;


int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " [port]" << std::endl;
        abort();
    }

    try {
        Registrar registrar((uint16_t)atoi(argv[1]));
        registrar.RegisterSection("SarumanTower");
        registrar.RegisterSection("Dungeon");
        registrar.UnregisterSection("Dungeon");
    } catch (sql::SQLException& e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }

    return 0;
}






// }  // namespace smartcampus


