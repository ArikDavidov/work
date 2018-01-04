#include "Logger.h"

#include <stdlib.h>

int main()
{
	size_t i;
	Log* log = NULL;

	log = GetLog("LogConfig.txt");

	for (i = 0; i < 10; ++i)
	{
		LOG_WRITE(log, LOG_CRITICAL, "testmsg-%d.%d", 1, i);		
	}
	
    return 0;
}

	



