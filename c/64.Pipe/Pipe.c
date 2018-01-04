#include <unistd.h>		/* getopt, pipe, fork, pause, write */
#include <stdlib.h>	
#include <stdio.h>
#include <string.h>		/* memset */
#include <sys/wait.h>	/* wait */

#define DEFAULT_NUM_OF_CYCLES	4
#define DEFAULT_BUFFER_SIZE 	256
#define SLEEP_TIME				250000


typedef struct
{
	size_t	m_nCycles;
	size_t	m_bufferSize;
} Params;


static int ArgsParser(int argc, char *argv[], Params* _params)
{
	int opt;

    while (-1 != (opt = getopt(argc, argv, "n:b:")))
    {
        switch (opt) 
        {
		    case 'n':
				_params->m_nCycles = (size_t)atoi(optarg);			break;
		    case 'b':
				_params->m_bufferSize = (size_t)atoi(optarg);		break;
		    default: /* '?' */
				fprintf(stderr, "Usage: %s [-n #] [-b #] \n",
						argv[0]);
		    	return 1;
        }
    }

	printf("m_nCycles=%d; m_bufferSize=%d\n",
			_params->m_nCycles, _params->m_bufferSize);

	return 0;
}

static void InitBuf(void* _buf, size_t _bufferSize)
{
	static char c = 'A';

	memset(_buf ,c, _bufferSize);
	++c;
}

static void ParentRoutine(int* _pipefd, Params* _params, char* _buf)
{
	size_t i;
	
	/* Close unused read end */
	close(_pipefd[0]);

	for (i = 0; i < _params->m_nCycles; ++i)
	{
		InitBuf((void*)_buf, _params->m_bufferSize);
		write(_pipefd[1], _buf, _params->m_bufferSize);
		/* TODO write() fails with EPIPE error + SIGPIPE signal */
		write(STDOUT_FILENO, "\n", 1);
		usleep(SLEEP_TIME);
	}
	
	close(_pipefd[1]);	/* Reader will see EOF */	
	wait(NULL);			/* Wait for child */
	exit(EXIT_SUCCESS);
}
	
static void ChildRoutine( int* _pipefd, Params* _params, char* _buf)
{
	/* Close unused write end */
	close(_pipefd[1]);

	while (read(_pipefd[0], _buf, _params->m_bufferSize) > 0)
	{
		write(STDOUT_FILENO, _buf, _params->m_bufferSize);
		usleep(SLEEP_TIME);
	}
	
	write(STDOUT_FILENO, "\n", 1);
	
	close(_pipefd[0]);
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
	Params params = {DEFAULT_NUM_OF_CYCLES, DEFAULT_BUFFER_SIZE};
	char* buf = NULL;
	int pipefd[2];
	pid_t pid;
	
	if(ArgsParser(argc, argv, &params))
	{
		exit(EXIT_FAILURE);
	}	
	
	buf = malloc(params.m_bufferSize * sizeof(char));
	
	if (-1 == pipe(pipefd)) 
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	pid = fork();
	if (pid < 0)
	{		
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		ParentRoutine(pipefd, &params, buf);
	}
	else
	{
		ChildRoutine(pipefd, &params, buf);
	}

	free(buf);
	
	return 0;
}






