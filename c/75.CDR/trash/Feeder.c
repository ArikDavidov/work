#include "Parser.h"
#include "MsgTransport.h"
#include "CDR.h"

#include <stdio.h>			/* FILE */
#include <stdlib.h>			/* exit */
#include <string.h>			/* strcmp, strcpy */
#include <assert.h>


#define CDR_FILE_NAME	"./Input/InputCdrTestScenario4.txt"
#define BUFFER_SIZE 	256


static FILE* OpenCdrFile(char* _cdrFileName)
{
	FILE* fp = NULL;
	
	assert(_cdrFileName);
	
	if(NULL == (fp = fopen(_cdrFileName, "r")))
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	return fp;
}

int main()
{
	FILE* fp = NULL;
	char line[BUFFER_SIZE];
	int mtid;
	MsgTransportBuf cdrBuf = {0};

	fp = OpenCdrFile(CDR_FILE_NAME);
	mtid = MsgTransportOpen();

	while(fgets(line, BUFFER_SIZE, fp))
	{
		Parse(line, &cdrBuf.m_cdr);
		MsgTransportSendCdr(mtid, &cdrBuf);
	}

	fclose(fp);

	return 0;
}

