#include <stdlib.h>		/* exit */
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_OF_PARAMETERS 50
#define STRING_SIZE 128


int readCommand(char* _str, char** _tokens)
{
	size_t i = 0;
	char delimiters[] = "\n";
	
	strtok(_string, delimiters);
	
	if (strcmp)
	{
	
	}
	
	
	while ()
	{
	
	}
	tokens[i + 1] = NULL;
	
	return 0;
}

int main()
{
	char str[STRING_SIZE];
	chcar* tokens[];

	while (1)
	{
		printf(">>>>> ");
		fgets();
		readCommand(str, tokens);
		
		
	forkParameter = fork();
	if (forkParameter < 0)
	{
		printf("Error\n");
		return -1;
	}
	/* Parent mode */
	else if (forkParameter > 0)
	{
		waitpid();
	}
	/* Child mode */
	else
	{
		execvp();
		printf("Command not found\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}
