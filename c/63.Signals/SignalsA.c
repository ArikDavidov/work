/*#define _POSIX_C_SOURCE 2*/

#include <unistd.h>		/* getopt, fork, pause, write */
#include <stdlib.h>	
#include <stdio.h>
#include <signal.h>		/* SIGINT, SIGILL */
#include <string.h>		/* strlen */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


volatile sig_atomic_t g_parentSignal = SIGINT;
volatile sig_atomic_t g_childSignal  = SIGILL;
volatile sig_atomic_t g_milliseconds = 200;

/*
Sigs
{
	volatile sig_atomic_t g_parentSignal = SIGINT;
	volatile sig_atomic_t g_childSignal  = SIGILL;
}
*/

int Parser(int argc, char *argv[])
{
	int opt;

    while ((opt = getopt(argc, argv, "p:c:s:")) != -1)
    {
        switch (opt) 
        {
		    case 'p':
				g_parentSignal = atoi(optarg);		break;
		    case 'c':
				g_childSignal  = atoi(optarg);		break;
		    case 's':
				g_milliseconds = atoi(optarg);		break;
		    default: /* '?' */
				fprintf(stderr, "Usage: %s [-p #] [-c #] [-s #] \n",
						argv[0]);
		    	return 1;
        }
    }

	printf("g_parentSignal=%d; g_childSignal=%d; g_milliseconds=%d\n",
			g_parentSignal, g_childSignal, g_milliseconds);

	return 0;
}

static void SigActionParentHandler(int sig, siginfo_t* siginfo, void* context)
{
	write(STDOUT_FILENO, "\nI am your father:\n", strlen("\nI am your father:\n") + 1);
}

static void SigActionChildHandler(int sig, siginfo_t* siginfo, void* context)
{
	char output[128];
	
	snprintf(output, 128, "Child recived the signal: %d",
			 (int)siginfo->si_pid);
	write(STDOUT_FILENO, output, strlen(output) + 1);

	kill(siginfo->si_pid, g_childSignal);
}

int main(int argc, char* argv[])
{
	pid_t pid;
	struct sigaction sa;
	
	if (Parser(argc, argv))
	{
		exit(EXIT_FAILURE);
	}	

	write(1, "Establishing...\n", strlen("Establishing...\n") + 1);
	sa.sa_sigaction = SigActionParentHandler;
	/* The SA_SIGINFO flag tells sigaction() to use the
		sa_sigaction field, not sa_handler. */
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	if (-1 == sigaction(g_parentSignal, &sa, NULL))
	{
	    perror("sigaction");
		exit(EXIT_FAILURE);
	}	
	pid = fork();
	if (pid < 0)
	{		
		printf("Fork failed\n");
	}
	else if (pid > 0)	/* Parent */
	{
		
		write(1, "Parent is entering sleep...\n", strlen("Parent is entering sleep...\n") + 1);
		usleep((useconds_t)g_milliseconds);
		
		kill(pid, g_parentSignal);

		write(1, "Parent is entering pause...\n", strlen("Parent is entering pause...\n") + 1);
		pause();
		write(1, "Parent exited pause...\n", strlen("Parent exited pause...\n") + 1);
	}
	else	/* Child */
	{
		write(1, "Child is entering pause...\n", strlen("Child is entering pause...\n") + 1);
		pause();
		write(1, "Child exited pause...\n", strlen("Child exited pause...\n") + 1);
	}
	
   exit(EXIT_SUCCESS);
}


    












