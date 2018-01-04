#include <stdio.h>
#include <stdlib.h>     /* rand */
#include <string.h>


#define MY_NETWORK 	8
#define LINES		5000


void CdrGenerate(char* _line);


int main()
{
	FILE* fp;
	char line[256];
	int i;

	fp = fopen("GeneratedCdr.txt","w");

	for (i = 0 ; i < LINES; ++i)
	{
		CdrGenerate(line);	
		fputs(line, fp);
	}

	fclose(fp);

	return 0;
}


void CdrGenerate(char* _line)
{
	char* callTypeLut[] = {"MOC", "MTC", "SMS-MO", "SMS-MT", "GPRS"};
	char imsi[16];
	char msisdn[16];
	char imei[16];
	char date[11];
	char time[9];
	char callData[64];
	char partyMsisdn[16];
	int subscriber = 0;
	int callType = 0;
	int operator = 0;
	int duration =0;

	subscriber = (rand() % 9) + 1;

	sprintf(imsi, "4250%d5%d%d1", MY_NETWORK, MY_NETWORK, subscriber * 1111111);
	sprintf(msisdn, "0009725%d%d", MY_NETWORK, subscriber * 1111111);
	sprintf(imei, "3525830735801%d%d", MY_NETWORK, subscriber);

	/* DD/MM/YYYY */
	sprintf(date, "%02d/%02d/%d", (rand() % 30) + 1, (rand() % 12) + 1, 1970 + (rand() % 50));
	/* HH:MM:SS */
	sprintf(time, "%02d:%02d:%02d", rand() % 24, rand() % 60, rand() % 60);

	if (4 == (callType = rand() % 5))
	{
		if (rand() % 2)
		{
			/* download */
			sprintf(callData, "0|%d.%d|0|0|0", rand() % 400, rand() % 100);
		}
		else
		{
			/* upload */
			sprintf(callData, "0|0|%d.%d|0|0", rand() % 15, rand() % 100);
		}
	}
	else
	{
		operator = (rand() % 8) + 1;
		sprintf(partyMsisdn, "0009725%d%d", operator, ((rand() % 9) + 1) * 1111111);

		if (2 > callType)
		{
			/* call */
			duration = rand() % 3600;
			sprintf(callData, "%d|0|0|%s|4250%d", duration, partyMsisdn, operator);
		}
		else
		{
			/* sms */
			sprintf(callData, "0|0|0|%s|4250%d", partyMsisdn, operator);
		}
	}

	sprintf(_line, "%s|%s|%s|Ariel Telecom Israel|42508|%s|%s|%s|%s\n",
			imsi, msisdn, imei, callTypeLut[callType], date, time, callData);
}







