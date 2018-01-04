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

static int FifoCreateAndOpen()
{	
	int fd;

	if (-1 == mkfifo(FIFO_NAME, RW_ONLY_PERMS)) 
	{
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	if (-1 == (fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK)))
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	printf("FIFO OPEN\n");

	return fd;
}

static void ListenToClients(int _fd, char* _buf, size_t _bufferSize)
{
	for(;;)
	{
		if (0 == read(_fd, _buf, _bufferSize))
		{
			break;
		}

		write(STDOUT_FILENO, "Server received: ", strlen("Server received: "));
		write(STDOUT_FILENO, _buf, _bufferSize);
		usleep(SLEEP_TIME);
	}
	
	write(STDOUT_FILENO, "\n", 1);
	
	write(STDOUT_FILENO, "EOF found\n", strlen("EOF found\n"));
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
	
    printf("Server - listening (PID: %d)\n", (int)getpid());
	
	buf = malloc(params.m_bufferSize * sizeof(char));

	fd = FifoCreateAndOpen();
	ListenToClients(fd, buf, params.m_bufferSize);

	close(fd);
	printf("FIFO Closed\n");

	return 0;
}

