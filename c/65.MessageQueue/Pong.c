



static int ArgsParser(int argc, char *argv[], Params* _params)
{
	int opt;

    while (-1 != (opt = getopt(argc, argv, "n:b:")))
    {
        switch (opt) 
        {
		    case 'v':
				_params->m_nCycles = (size_t)atoi(optarg);			break;
		    case 's':
				_params->m_bufferSize = (size_t)atoi(optarg);		break;
			case 'f':
				_params->m_bufferSize = (size_t)atoi(optarg);		break;
		    default: /* '?' */
				fprintf(stderr, "Usage: %s [-v #] [-s #] [-f #]\n", 
						argv[0]);
		    	return 1;
        }
    }

	printf("m_nCycles=%d; m_bufferSize=%d\n",
			_params->m_nCycles, _params->m_bufferSize);

	return 0;




if (verbosity)
{
	fprint(std, 
}


