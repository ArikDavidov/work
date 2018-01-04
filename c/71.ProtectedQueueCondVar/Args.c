#include "Args.h"

#include <unistd.h>     /* getopt */
#include <stdlib.h>     /* atoi */
#include <stdio.h>		/* fprintf */

void ArgsParser(int argc, char *argv[], InParams* _params)
{
	int opt;

    while (-1 != (opt = getopt(argc, argv, "p:c:m:s:")))
    {
        switch (opt) 
        {
			case 'p':
				_params->m_nProducers = atoi(optarg);			break;
		    case 'c':
				_params->m_nConsumers = atoi(optarg);			break;
		    case 'm':
				_params->m_nMsgs = atoi(optarg);				break;
			case 's':
				_params->m_qSize = atoi(optarg);				break;
		    default: /* '?' */
				fprintf(stderr, "Usage: %s [-p #] [-c #] [-m #] [-s #]\n",
						argv[0]);
				exit(EXIT_FAILURE);
		}
	}
}





