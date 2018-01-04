#include "Parser.h"
#include "MsgTransport.h"
#include "CDR.h"

#include <stdio.h>			/* FILE */
#include <stdlib.h>			/* exit */
#include <sys/types.h>		/* getpid */
#include <unistd.h>			/* getpid */
#include <string.h>			/* strlen */
#include <linux/limits.h>	/* PATH_MAX */
#include <assert.h>

#define WORK_PATH					"./WorkInProgress"	/* TODO move to config file */
#define DONE_PATH					"./Done"			/* TODO move to config file */
#define CDR_FILE_NAME				argv[1]
#define	IS_BUFFER_OVERFLOW(P, N)	(PATH_MAX < strlen(P) + strlen(N) + 2)	/* including '/' and '\0' */
#define LINE_BUFFER_SIZE 			256

/*
#define HANDLE_ERROR(M)						do{perror(M);exit(EXIT_FAILURE);}	\
												while(0)
*/

static FILE* OpenCdrFile(const char* _workPath, const char* _cdrFileName)
{
	FILE* fp = NULL;
	char workFileName[PATH_MAX];
	
	assert(_cdrFileName);
	assert(!IS_BUFFER_OVERFLOW(_workPath, _cdrFileName));
	
	sprintf(workFileName, "%s/%s", _workPath, _cdrFileName);
	/* printf("%s", workFileName); */
	if(NULL == (fp = fopen(workFileName, "r")))
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	return fp;
}

static void MoveCdrToDoneDir(const char* _workPath, const char* _donePath, char* _cdrFileName)
{
	char workFileName[PATH_MAX];
	char doneFileName[PATH_MAX];

	assert(_workPath);
	assert(_donePath);
	assert(_cdrFileName);
	assert(!IS_BUFFER_OVERFLOW(_donePath, _cdrFileName));

	printf("Moveing to done\n");
	sprintf(doneFileName, "%s/%s", _donePath, _cdrFileName);
	sprintf(workFileName, "%s/%s", _workPath, _cdrFileName);
	
	if (-1 == rename(workFileName, doneFileName))
	{
		perror("rename");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	FILE* fp = NULL;
	int mtid;
	MsgTransportBuf cdrBuf = {0};
	char line[LINE_BUFFER_SIZE];
	pid_t pid;
	
	usleep(200);
	pid = getpid();
	printf("Feeder pid: %d\n", pid);
	
	if(!CDR_FILE_NAME)
	{
		fprintf(stderr, "Error: argv[1] = \"%s\"\n", CDR_FILE_NAME);
		exit(EXIT_FAILURE);
	}
	
	printf("%s\n", CDR_FILE_NAME);
	mtid = MsgTransportOpen();
	/* TODO cheks */
	
	fp = OpenCdrFile(WORK_PATH, CDR_FILE_NAME);
	
	while(fgets(line, LINE_BUFFER_SIZE, fp))
	{
		Parse(line, &cdrBuf.m_cdr);
		/* TODO cheks */
		MsgTransportSendCdr(mtid, &cdrBuf);
		/* TODO cheks */
	}

	fclose(fp);
	
	MoveCdrToDoneDir(WORK_PATH, DONE_PATH, CDR_FILE_NAME);
	
	printf("Feeder is exiting. pid: %d\n", pid);
	exit(EXIT_SUCCESS);
}






