#include "SmartHome.h"
#include "Hub.h"
#include "ConfigParser.h"
#include "Loader.h"
#include "AgentData.h"
#include "AgentFactory.h"

#include <unistd.h>
#include <iostream>


int main()
{
    SmartHome myHome("HauntedHouse.ini");
    
    myHome.Init();
    
    usleep(3000000);
    std::cout << "sleep" << std::endl;
    
    return 0;
}


