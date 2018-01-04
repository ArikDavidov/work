#include "Processor.h"
#include "CGF.h"
#include "Subscribers.h"
#include "Operators.h"

#include <stdio.h>
#include <stdlib.h>			/* exit */
#include <string.h>			/* strlen */ 

#define IMSI_LENGTH		15
#define MSISDN_LENGTH	15
#define IMEI_LENGTH		15
#define BRAND_LENGTH	64
#define MCC_MNC_LENGTH	6


void CgfOperatorRetrieveQuery(Processor* _processor, char* _buf)
{
	char partyOperator[MCC_MNC_LENGTH + 1];
	Operator* operator = NULL;

	if(!_processor)
	{
		fprintf(stderr, "CgfOperatorRetrieveQuery: _processor uninitialized\n");
		exit(EXIT_FAILURE);
	}
	if (!_buf)
	{
		fprintf(stderr, "CgfOperatorRetrieveQuery: invalid argument\n");
		exit(EXIT_FAILURE);
	}

	sscanf(_buf, "%*d %s", partyOperator);
	printf("CgfOperatorRetrieveQuery:partyOperator: %s\n", partyOperator);
	
	operator = OperatorsFindOperator(_processor->m_operators, partyOperator);
	if (!operator)
	{
		sprintf(_buf, "Operator %s was not found.\n", partyOperator);
	}

	sprintf(_buf, "%s, ", partyOperator);
	printf("strlen(_buf): %d\n", strlen(_buf));
	OperatorsWriteOperatorToString(_processor->m_operators, partyOperator,
									operator, _buf + strlen(_buf));
	printf("%s\n", _buf);
}

void CgfSubscriberRetrieveQuery(Processor* _processor, char* _buf)
{
	char msisdn[MSISDN_LENGTH + 1];
	Subscriber* subscriber = NULL;

	if(!_processor)
	{
		fprintf(stderr, "CgfSubscribersRetrieveQuery: _processor uninitialized\n");
		exit(EXIT_FAILURE);
	}
	if (!_buf)
	{
		fprintf(stderr, "CgfSubscribersRetrieveQuery: invalid argument\n");
		exit(EXIT_FAILURE);
	}

	sscanf(_buf, "%*d %s", msisdn);
	printf("CgfSubscribersRetrieveQuery:msisdn: %s\n", msisdn);
	
	subscriber = SubscribersFindSubscriber(_processor->m_subscribers, msisdn);
	if (!subscriber)
	{
		sprintf(_buf, "Subscriber %s was not found.\n", msisdn);
	}

	sprintf(_buf, "%s, ", msisdn);
	printf("strlen(_buf): %d\n", strlen(_buf));
	SubscribersWriteSubscriberToString(_processor->m_subscribers, msisdn, subscriber,
										_buf + strlen(_buf));
	printf("%s\n", _buf);
}



/*
CGFResult CgfMsisdnRetrieveQuery(CGF* _cgf, char* _buf)
{
	Subscriber* subscriber = NULL;


	Subscriber* SubscribersFindSubscriber(Subscribers* _subscribers, const Cdr* _cdr)
}

CGFResult CgfAllSubscribersReport(CGF* _cgf);
	create file for writing
	fp = fopen("./Reports/AllSubscribersReport", "w")	//"a"?
	fprintf(fp, "%s\n", );
*/

/*
CGFResult CgfAllOperatorsReport(CGF* _cgf)
{	
	FILE* fp;
	Operator* operator = NULL;
	
	fp = fopen("GeneratedCdr.txt","w");

	for(;;)
	{
		operator = OperatorsFindOperator(_cfg->m_operators, const Cdr* _cdr);
		if (!operator)
		{
			
			
		}
		OperatorPrint(Operator* _operator, char* _buf, unsigned int _len)
	}
	
	fclose(fp);
}


int main()
{
	char line[256];
	int i;


	for (i = 0 ; i < LINES; ++i)
	{
		CdrGenerate(line);	
		fputs(line, fp);
	}


	return 0;
}
*/




