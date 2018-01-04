		#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>		/* getopt, pipe, fork, pause, write */
#include <string.h>		/* memset */
#include <sys/wait.h>	/* wait */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>		/* O_NONBLOCK, O_WRONLY */

#define FIFO_NAME				"MyPipe"
#define RW_ONLY_PERMS			0666
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

static void SendToServer(int _fd, Params* _params, char* _buf)
{
	size_t i;

	for (i = 0; i < _params->m_nCycles; ++i)
	{
		InitBuf((void*)_buf, _params->m_bufferSize);
		write(_fd, _buf, _params->m_bufferSize);
		/* TODO write() fails with EPIPE error + SIGPIPE signal */
		write(STDOUT_FILENO, "\n", 1);
		usleep(SLEEP_TIME);
	}

}

int main(int argc, char* argv[])
{
	Params params = {DEFAULT_NUM_OF_CYCLES, DEFAULT_BUFFER_SIZE};
	char* buf = NULL;
	int fd;
    
	if(ArgsParser(argc, argv, &params))
	{
		exit(EXIT_FAILURE);
	}
	
	printf("Client -  (PID: %d)\n", (int)getpid());
	
	if (NULL == (buf = malloc(params.m_bufferSize * sizeof(char))))
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (-1 == (fd = open(FIFO_NAME, O_WRONLY)))
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	SendToServer(fd, &params, buf);

	close(fd);

	return 0;
}




