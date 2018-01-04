#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define PRINTF_DEBUG	printf("IMSI: %s", _buf);

typedef enum CallType
{
	MOC,		/**< outgoing voice call  */
	MTC,		/**< incomming voice call */
	SMS_MO,		/**< outgoing message     */
	SMS_MT,		/**< incomming message    */
	GPRS		/**< internet             */
} CallType;

typedef struct TestCdrRecord
{
	char	m_imsi[15 + 1];					/**< 													*/
	char	m_msisdn[15 + 1];				/**< Subscriber ID in a mobile network					*/
	char	m_imei[15 + 1];					/**< Subscriber Equipment number: 49-015420-323751		*/
	char	m_operatorBrandName[64 + 1];	/**< for example: "Cellcom Israel"						*/
	char	m_mccMnc[5 + 1];				/**< 													*/
	char	m_testCallType[6 + 1];			/**< FOR TESTS ONLY: char instead of CallType			*/
	char	m_callDate[10 + 10];			/**< DD/MM/YYYY											*/
	char	m_callTime[8 + 1];				/**< HH:MM:SS											*/
	int		m_duration;						/**< in seconds											*/
	int		m_download;						/**< MB dowloaded if type is GPRS						*/
	int		m_upload;						/**< MB uploaded if type is GPRS						*/
	char	m_partyMsisdn[15 + 1];			/**< Corresponding party in this call, empty for GPRS	*/
	char	m_partyOperator[5 + 1];			/**< Corresponding party’s mobile operator in this call	*/
} TestCdrRecord;


static void GenerateNumString(char* _buf, int _length)
{
	int i;
	
	for (i = 0; i < _length; ++i)
	{
		_buf[i] = (char)('0' + rand() % 10);
	}
	_buf[_length] = '\0';
}

static void GenerateDuration(int* _duration)
{
	*_duration = (rand() % 600) + (rand() % 3600) * (rand() % 2);
}

static void GenerateMegaBytes(int* _mb)
{
	*_mb = rand() % 128;
}

/* HH:MM:SS */
static void GenerateTime(char* _buf)
{
	sprintf(_buf, "%02d:%02d:%02d", rand() % 24, rand() % 60, rand() % 60);
	/*_buf[8] = '\0';*/
}

/* DD/MM/YYYY */
static void GenerateDate(char* _buf)
{
	sprintf(_buf, "%02d/%02d/%d", (rand() % 30) + 1, (rand() % 12) + 1, 1970 + (rand() % 50));
	/*_buf[11] = '\0';*/
}

/* TODO GenerateCallType();*/


static void GenerateCdr()
{
	TestCdrRecord cdrRec;

	GenerateNumString(cdrRec.m_imsi, 15);
	GenerateNumString(cdrRec.m_msisdn, 15);
	GenerateNumString(cdrRec.m_imei, 15);
	strncpy(cdrRec.m_operatorBrandName, "Cellcom Israel", 64);
	GenerateNumString(cdrRec.m_mccMnc, 5);
	strncpy(cdrRec.m_testCallType, "MOC", 6);
	GenerateDate(cdrRec.m_callDate);
	GenerateTime(cdrRec.m_callTime);
	GenerateDuration(&cdrRec.m_duration);
	GenerateMegaBytes(&cdrRec.m_download);
	GenerateMegaBytes(&cdrRec.m_upload);
	GenerateNumString(cdrRec.m_partyMsisdn, 15);
	GenerateNumString(cdrRec.m_partyOperator, 5);

	printf("%s|%s|%s|%s|%s|%s|%s|%s|%d|%d|%d|%s|%s\n",
				cdrRec.m_imsi, cdrRec.m_msisdn,	cdrRec.m_imei,
				cdrRec.m_operatorBrandName, cdrRec.m_mccMnc, cdrRec.m_testCallType,
				cdrRec.m_callDate, cdrRec.m_callTime, cdrRec.m_duration,
				cdrRec.m_download, cdrRec.m_upload, cdrRec.m_partyMsisdn,
				cdrRec.m_partyOperator);
}


int main()
{
	int i;

	for (i = 0; i < 5; ++i)
	{		
		GenerateCdr();
	}
	/*
	printf("%s\n", cdrRec.m_imsi);
	printf("%s\n", cdrRec.m_msisdn);
	printf("%s\n", cdrRec.m_imei);
	printf("%s\n", cdrRec.m_operatorBrandName);
	printf("%s\n", cdrRec.m_mccMnc);
	printf("%s\n", cdrRec.m_testCallType);
	printf("%s\n", cdrRec.m_callDate);
	printf("%s\n", cdrRec.m_callTime);
	printf("%d\n", cdrRec.m_duration);
	printf("%d\n", cdrRec.m_download);
	printf("%d\n", cdrRec.m_upload);
	printf("%s\n", cdrRec.m_partyMsisdn);
	printf("%s\n", cdrRec.m_partyOperator);
	*/
	
	return 0;

}





