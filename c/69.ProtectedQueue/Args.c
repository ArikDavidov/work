#include "Args.h"




void ArgsParser(int argc, char *argv[], InParams* _params)
{
	int opt;

    while (-1 != (opt = getopt(argc, argv, "p:c:m:s:")))
    {
        switch (opt) 
        {
			case 'p':
				_params->m_createMQ = atoi(optarg);				break;
		    case 'c':
				_params->m_deleteMQ = atoi(optarg);				break;
		    case 'm':
				_params->m_deleteMQ = atoi(optarg);				break;
			case 's':
				_params->m_deleteMQ = atoi(optarg);				break;
		    default: /* '?' */
				fprintf(stderr, "Usage: %s [-p #] [-c #] [-m #] [-s #]\n",
						argv[0]);
				exit(EXIT_FAILURE);
		}
	}
}





