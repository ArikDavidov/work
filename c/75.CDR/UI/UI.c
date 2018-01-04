#include "MsgTransport.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


#define IMSI_LENGTH		15
#define MSISDN_LENGTH	15
#define IMEI_LENGTH		15
#define BRAND_LENGTH	64
#define MCC_MNC_LENGTH	6


int main()
{
	char mccMnc[MCC_MNC_LENGTH + 1];
	char msisdn[MSISDN_LENGTH + 1];
	MsgTransportBuf queryBuf = {0};
	//char buf[256];
	int  mtid = 0;
	int  option = 0;
	int  cont = 1;			/* trigger to stop loop */

	//cgf = CgfCreate();
	mtid = MsgTransportOpen();

	while (cont) 
	{
		printf("							\n");
		printf("Choose option:				\n");
		printf("0: Msisdn Retrieve Query	\n");
		printf("1: Operator Retrieve Query	\n");
		printf("2: All Subscribers Report	\n");
		printf("3: All Operators Report		\n");
		printf("4: Pause					\n");
		printf("5: Resume					\n");
		printf("6: System shut Down			\n");
		printf("Any other number - Quit UI	\n");
		
		scanf("%d", &option);
		switch (option) 
		{
			case 0:
				printf("\nPlease enter Subscriber's msisdn\n");
				scanf("%s", msisdn);
				assert(MSISDN_LENGTH >= strlen(msisdn));
				
				sprintf((char*)&queryBuf.m_cdr, "%d %s", option, msisdn);
				MsgTransportSendQuery(mtid, &queryBuf);
				usleep(200);
				MsgTransportGetReply(mtid, &queryBuf);
				
				printf("\nQueryReply: %s\n", (char*)&queryBuf.m_cdr);	break;
			case 1:
				printf("\nPlease enter operator's MCC/MNC:\n");
				scanf("%s", mccMnc);
				assert(5 == strlen(mccMnc) || 6 == strlen(mccMnc));
				
				sprintf((char*)&queryBuf.m_cdr, "%d %s", option, mccMnc);
				MsgTransportSendQuery(mtid, &queryBuf);
				usleep(200);				
				MsgTransportGetReply(mtid, &queryBuf);
				
				printf("\nQueryReply: %s\n", (char*)&queryBuf.m_cdr);	break;
			case 2:
				printf("\nProducing All Subscribers Report\n");
				
				sprintf((char*)&queryBuf.m_cdr, "%d", option);
				MsgTransportSendQuery(mtid, &queryBuf);

				MsgTransportGetReply(mtid, &queryBuf);
				
				printf("\nAll Subscribers Report is ready\n");			break;
			case 3:
				printf("\nProducing All Operators Report\n");
				
				sprintf((char*)&queryBuf.m_cdr, "%d", option);
				MsgTransportSendQuery(mtid, &queryBuf);

				MsgTransportGetReply(mtid, &queryBuf);
				
				printf("\nAll Operators Report is ready\n");			break;
			/*
			case 4:
				Destroy(calendar);
				calendar=NULL;
				printf("\nCalendar was destroyd!\n");					break;
			case 5:
				tempReturned = PrintCalendar(calendar);
				if(tempReturned==-1){
					printf("\nCalendar was not found.\n");
				}														break;
			*/
			default: cont = 0;											break;
		}
	}


	return 0;
}

