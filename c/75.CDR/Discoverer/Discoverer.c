#include <stdio.h>
#include <stdlib.h>			/* exit */
#include <unistd.h>
#include <string.h>			/* strlen, strrchr */ 
#include <sys/wait.h>		/* wait */
#include <sys/types.h>		/* wait, opendir, readdir, rewinddir */
#include <dirent.h>			/* opendir, readdir, rewinddir */
#include <errno.h>
#include <assert.h>

#define MAX_NUM_OF_FEDDERS			4
#define FILE_EXTENTION				"cdr"					/* TODO move to config file */
#define INPUT_PATH					"./Input"				/* TODO move to config file */
#define WORK_PATH					"./WorkInProgress"		/* TODO move to config file */
#define FEEDER_FILE_PATH 			"./Feeder/Feeder"		/* TODO move to config file */
#define POLLING_INTERVAL			4000000					/* TODO move to config file */
#define	IS_BUFFER_OVERFLOW(P, N)	(PATH_MAX < strlen(P) + strlen(N) + 2)	/* including '/' and '\0' */	

/*
#define HANDLE_ERROR(M)						do{perror(M);exit(EXIT_FAILURE);}	\
												while(0)
*/

const char* GetFileExtension(const char* _filename)
{
    const char* dot = strrchr(_filename, '.');
    
    return (!dot || dot == _filename) ?  "" : dot + 1;
}

static void MoveCdrToWorkDir(const char* _inputPath, const char* _workPath, char* _cdrFileName)
{
	char inputFileName[PATH_MAX];
	char workFileName[PATH_MAX];

	assert(_inputPath);
	assert(_workPath);
	assert(_cdrFileName);
	assert(!IS_BUFFER_OVERFLOW(_inputPath, _cdrFileName));
	assert(!IS_BUFFER_OVERFLOW(_workPath, _cdrFileName));

	sprintf(inputFileName, "%s/%s", _inputPath, _cdrFileName);
	sprintf(workFileName, "%s/%s", _workPath, _cdrFileName);
	
	if (-1 == rename(inputFileName, workFileName))
	{
		perror("rename");
		exit(EXIT_FAILURE);
	}
}

static void WaitIfReachedMaxNumOfFeeders(int* _nFeeders)
{
	printf("nFeeders: %d\n", *_nFeeders);
	
	if (MAX_NUM_OF_FEDDERS <= *_nFeeders)
	{
		/* Wait for any child process */
		if (-1 == wait(NULL))
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		--*_nFeeders;
	}		
}

int main(int argc, char *argv[])
{
	DIR* dirp = NULL;
	struct dirent* dp;
	char* newargv[] = {FEEDER_FILE_PATH, NULL, NULL};
	char *newenviron[] = {NULL};
	pid_t pid;
	int nFeeders = 0;
	
	dirp = opendir(INPUT_PATH);

	for (;/*!shutDownMode*/;)
	{
		errno = 0;
		
		/* Reached end of directory */
		if (NULL == (dp = readdir(dirp)))
		{
			usleep(POLLING_INTERVAL);
			rewinddir(dirp);
			continue;
		}

		/* Skipping '..' and '.' enteries */
		if (DT_DIR == dp->d_type)
		{
			continue;
		}

		if (strcmp(FILE_EXTENTION, GetFileExtension(dp->d_name)))
		{
			continue;
		}

		printf("%s\n", dp->d_name);
		MoveCdrToWorkDir(INPUT_PATH, WORK_PATH, dp->d_name);
		
		newargv[1] = dp->d_name;
		printf("%s\n", newargv[1]);
		
		pid = fork();
		if (-1 == pid)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}		
		if (pid == 0)	/* Child process */
		{
			execve(newargv[0], newargv, newenviron);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		else	/* Parent process */
		{
			++nFeeders;
			WaitIfReachedMaxNumOfFeeders(&nFeeders);
		}
		
	}

	closedir(dirp);
	printf("Discoverer is exiting\n");
	exit(EXIT_SUCCESS);
}




	//char* ext = NULL;
			//execvp(newargv[0],newargv);
/*
			if (MAX_NUM_OF_FEDDERS == nFeeders)
			{
				if (-1 == wait(NULL))	
				{
					perror("wait");
					exit(EXIT_FAILURE);
				}
				--nFeeders;
				printf("nFeeders: %d\n", nFeeders);
			}
main()
{
    int i,pid[3];
    for(i=0;i<3;i++)
    {
        pid[i]=fork();
        if (pid[i]==0)
            execl("path",0,0);
    }

    sleep(2);
}
execvp();
execve() returns only on error

char* arg[] = {"ls", "-l", NULL};
execvp(arg[0],arg);
*/




