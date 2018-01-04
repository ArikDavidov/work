/**
 * @brief: generate a number of (identical) configurable CDR files
 * @detail: 
 	for each file, repeats N_REPETITIONS times and writes for each subscriber x operator combination nine standard CDR lines: 
 	1. outgoing call within the operator
 	2. outgoing call to party operator (represented by _partyMCCMNC)
 	3. incoming call within the operator
 	4. incoming call to party operator (represented by _partyMCCMNC)
 	5. outgoing SMS within the operator
 	6. outgoing SMS to party operator (represented by _partyMCCMNC)
 	7. incoming SMS within the operator
 	8. incoming SMS to party operator (represented by _partyMCCMNC)
 	9. GPRS
 	
 	call durations and upload/download MB are also configurable
 
 * @note: total number of lines in each CDR file will be 9 X N_SUBSCRIBERS x N_OPERATORS x N_REPETITIONS
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================= 	*/
/*			DEFINITIONS				*/
/* ============================= 	*/
typedef struct
{
	unsigned int	m_subscribers;
	unsigned int	m_operators;
	unsigned int	m_repetitions;
	unsigned int	m_files;
	unsigned int	m_out_within;
	unsigned int	m_out_without;
	unsigned int	m_in_within;
	unsigned int	m_in_without;
	double			m_down;
	double			m_up;
}Configuration;
/* ============================= 	*/	
#define FILE_EXTENSION ".cdr"	
#define FILE_TARGET	"../GenCDRs/"
/* ============================= 	*/
/*default configuration*/
#define N_SUBSCRIBERS 	1000 	/*default number of different subscribers*/
#define N_OPERATORS		10 	/*default number of different operators*/
#define N_REPETITIONS	10		/*default number of times standard CDR registries will be written for each subsciberXoperator combination*/
#define N_FILES 		5		/*default number of (identical) files*/

#define STD_OUT_WITHIN_DUR	1		/*standard outgoing call duration within same operator*/
#define STD_OUT_WITHOUT_DUR	10		/*standard outgoing call duration to party operator*/
#define STD_IN_WITHIN_DUR	100		/*standard incoming call duration within same operator*/
#define STD_IN_WITHOUT_DUR	1000	/*standard incoming call duration to party operator*/
#define STD_DOWN			0.1		/*standard amount of MBs downloaded*/
#define	STD_UP				0.01	/*standard amount of MBs uploaded*/
/* ============================= */	
typedef struct Sub
{
    char            m_IMSI[16];
    char            m_MSISDN[16];
    char            m_IMEI[16];
}Sub;
/* ============================= 	*/
/*		AUX FUNCTION DECLARATION	*/
/* ============================= 	*/
static void GetParametersFromUser(Configuration* _config);
static void SetDefaults(Configuration* _config);

/**
 * @brief: generate an array of Subs
 * @detail: IMSIs range from 100000000000000 - 100000000000000+_nSubs
 			MSISDNs range from 200000000000000 - 200000000000000+_nSubs
  			IMEIs range from 300000000000000 - 300000000000000+_nSubs
 */	
static Sub* GenerateSubscriberArray(unsigned int _nSubs);
static void GenerateIMSI(char* _IMSI, int _index);
static void GenerateMSISDN(char* _MSISDN, int _index);
static void GenerateIMER(char* _IMEI, int _index);

/**
 * @brief: generate an array of MCCMNC tuples
 * @detail: MCCMNCs range from 10000 - 100000+_nOperators
 */
static int* GenerateOperatorArray(unsigned int _nOperators);

static void GenerateFile(int fileNum, Sub* _subArray, int* _oprArray, Configuration* _config);

static void myLItoa(unsigned long long _integer, char* _buffer);
static void ReverseString(char* _dest, char* _source);

/**
 * @brief: writes nine standard CDR lines into _file regarding given subscriber and party operator
 * @detail: each CDR line represents a different charging event:
 	1. outgoing call within the operator
 	2. outgoing call to party operator (represented by _partyMCCMNC)
 	3. incoming call within the operator
 	4. incoming call to party operator (represented by _partyMCCMNC)
 	5. outgoing SMS within the operator
 	6. outgoing SMS to party operator (represented by _partyMCCMNC)
 	7. incoming SMS within the operator
 	8. incoming SMS to party operator (represented by _partyMCCMNC)
 	9. GPRS
 * @detail: standard call durations and downloaded/uploaded MBs are #defined above
 */
static void WriteStandardCDRs(FILE* _file, Sub _subscriber, int _partyMCCMNC, Configuration* _config);

/* ============================= 	*/
/*			MAIN					*/
/* ============================= 	*/	
int main()
{
    int* operators;
    Sub* subs;
    int i;
 	Configuration config;
 	
 	GetParametersFromUser(&config);
 	
    subs = GenerateSubscriberArray(config.m_subscribers);
    operators = GenerateOperatorArray(config.m_operators);
    
    for (i = 0; i < config.m_files; ++i)
    {
    	printf("making file no. %d\n", i+1);
    	GenerateFile(i, subs, operators, &config);
    }

}
/* ============================= 	*/
/*		AUX FUNCTION DEFINITION		*/
/* ============================= 	*/
static void GetParametersFromUser(Configuration* _config)
{
	int userChoice = 0;
	
	while (userChoice != 1 && userChoice != 2)
	{
		printf("configure parameters or set defaults?\n[1] configure\n[2] default\n");
	
		scanf("%d", &userChoice);
		
		if (userChoice == 2)
		{
			SetDefaults(_config);
			return;
		}		
	}
	printf("enter number of files to generate\n");
	scanf("%d", &(_config->m_files));
	
	printf("enter number of subscribers\n");
	scanf("%d", &(_config->m_subscribers));
	
	printf("enter number of operators\n");
	scanf("%d", &(_config->m_operators));
	
	printf("enter number of times standard CDR enrties will be written for each operator x subscriber combination\n");
	scanf("%d", &(_config->m_repetitions));
	
	printf("enter standard outgoing call duration within same operator\n");
	scanf("%d", &(_config->m_out_within));
	
	printf("enter standard outgoing call duration to external operator\n");
	scanf("%d", &(_config->m_out_without));
	
	printf("enter standard incoming call duration within same operator\n");
	scanf("%d", &(_config->m_in_within));
	
	printf("enter standard incoming call duration from external operator\n");
	scanf("%d", &(_config->m_in_without));
	
	printf("enter standard amount of MBs downloaded\n");
	scanf("%lf", &(_config->m_down));

	printf("enter standard amount of MBs uploaded\n");
	scanf("%lf", &(_config->m_up));
}
/* ============================= 	*/
static void SetDefaults(Configuration* _config)
{
	_config->m_operators = N_OPERATORS;
	_config->m_subscribers = N_SUBSCRIBERS;
	_config->m_repetitions = N_REPETITIONS;
	_config->m_files= N_FILES;
	_config->m_out_within = STD_OUT_WITHIN_DUR;
	_config->m_out_without = STD_OUT_WITHOUT_DUR;
	_config->m_in_within = STD_IN_WITHIN_DUR;
	_config->m_in_without = STD_IN_WITHOUT_DUR;
	_config->m_down = STD_DOWN;
	_config->m_up = STD_UP;	
}
/* ============================= 	*/
static Sub* GenerateSubscriberArray(unsigned int _nSubs)
{
	int i;
	Sub* subArray;
	
	if (!(subArray = malloc(sizeof(Sub) * _nSubs)))
	{
		printf("SUB ARRAY MALLOC FAILURE\n");
		exit(1);
	}
	
	for (i = 0; i < _nSubs; ++i)
	{
		GenerateIMSI(subArray[i].m_IMSI, i);
		GenerateMSISDN(subArray[i].m_MSISDN, i);
		GenerateIMER(subArray[i].m_IMEI, i);
	}
	
	return subArray;
}
/* ============================= 	*/
static void GenerateIMSI(char* _IMSI, int _index)
{
	unsigned long long IMSI;
	IMSI = 100000000000000 + _index;
	myLItoa(IMSI, _IMSI);
}
/* ============================= 	*/
static void GenerateMSISDN(char* _MSISDN, int _index)
{
	unsigned long long MSISDN;
	MSISDN = 200000000000000 + _index;
	myLItoa(MSISDN, _MSISDN);
}
/* ============================= 	*/
static void GenerateIMER(char* _IMEI, int _index)
{
	unsigned long long IMEI;
	IMEI = 300000000000000 + _index;
	myLItoa(IMEI, _IMEI);
}
/* ============================= 	*/
static int* GenerateOperatorArray(unsigned int _nOperators)
{
	int i;
	int * oprArray;
	
	if (!(oprArray = malloc(sizeof(int) * _nOperators)))
	{
		printf("OPR ARRAY MALLOC FAILURE\n");
		exit(1);
	}
	
	for (i = 0; i < _nOperators; ++i)
	{
		oprArray[i] = 10000 + i;
	}
	
	return oprArray;
}	
/* ============================= 	*/
static void GenerateFile(int fileNum, Sub* _subArray, int* _oprArray, Configuration* _config)
{
	FILE* fp;
	char fileName[64];
	int repIndex, oprIndex, subIndex;
	
    sprintf(fileName, "%sCDRFile%d%s", FILE_TARGET, fileNum, FILE_EXTENSION);
    fp = fopen(fileName, "w");
    perror("zz");
    fprintf(fp,"CDR HEADER\n");
    
    for (repIndex = 0; repIndex < _config->m_repetitions; ++repIndex)
    {
    	for (subIndex = 0; subIndex < _config->m_subscribers ; ++subIndex)
    	{
    		for (oprIndex = 0; oprIndex < _config->m_operators ; ++oprIndex)
    		{
    			WriteStandardCDRs(fp, _subArray[subIndex], _oprArray[oprIndex], _config);
    		}
    	}	
    }
    
    fclose(fp);
}
/* ============================= 	*/
static void WriteStandardCDRs(FILE* _file, Sub _subscriber, int _partyMCCMNC, Configuration* _config)
{
	/*standard common CDR fields*/
	const char dateAndTime[] = "01/01/01|11:11:11";
	const char brandName[] = "Pellular Inc.";
	const int brandMCCMNC = 9999;
	const char partyMSISDN[] = "123456789876543";

	
	/*1. outgoing call within the operator*/
	fprintf (_file, "%s|%s|%s|%s|%u|MOC|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, _config->m_out_within, 0.0, 0.0, partyMSISDN, brandMCCMNC);
	
	/*2. outgoing call to party operator (represented by _partyMCCMNC)*/
	fprintf (_file, "%s|%s|%s|%s|%u|MOC|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, _config->m_out_without, 0.0, 0.0, partyMSISDN, _partyMCCMNC);
	
 	/*3. incoming call within the operator*/
 	fprintf (_file, "%s|%s|%s|%s|%u|MTC|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, _config->m_in_within, 0.0, 0.0, partyMSISDN, brandMCCMNC);
 	
 	/*4. incoming call to party operator (represented by _partyMCCMNC)*/
 	fprintf (_file, "%s|%s|%s|%s|%u|MTC|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, _config->m_in_without, 0.0, 0.0, partyMSISDN, _partyMCCMNC);
 	
 	/*5. outgoing SMS within the operator*/
 	fprintf (_file, "%s|%s|%s|%s|%u|SMS-MO|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, 0, 0.0, 0.0, partyMSISDN, brandMCCMNC);
 	
 	/*6. outgoing SMS to party operator (represented by _partyMCCMNC)*/
 	fprintf (_file, "%s|%s|%s|%s|%u|SMS-MO|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, 0, 0.0, 0.0, partyMSISDN, _partyMCCMNC);
 	
 	/*7. incoming SMS within the operator*/
 	fprintf (_file, "%s|%s|%s|%s|%u|SMS-MT|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, 0, 0.0, 0.0, partyMSISDN, brandMCCMNC);
 	
 	/*8. incoming SMS to party operator (represented by _partyMCCMNC)*/
 	fprintf (_file, "%s|%s|%s|%s|%u|SMS-MT|%s|%u|%.3lf|%.3lf|%s|%u\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, 0, 0.0, 0.0, partyMSISDN, _partyMCCMNC);
 	
 	/*9. GPRS*/
 	fprintf (_file, "%s|%s|%s|%s|%u|GPRS|%s|%u|%.3lf|%.3lf|%s|X\n", _subscriber.m_IMSI, _subscriber.m_MSISDN, _subscriber.m_IMEI, brandName, brandMCCMNC, dateAndTime, 0, _config->m_down, _config->m_up, partyMSISDN);

}
/* ============================= 	*/
static void myLItoa(unsigned long long _integer, char* _buffer)
{
	char reversed[32];
	int i;
	
	for (i = 0; _integer != 0 ; ++i)
	{
		reversed[i] = (_integer % 10) + '0';
		_integer /= 10;
	}
	
	reversed[i] = '\0';
	
	ReverseString(_buffer, reversed);
}
/* ============================= 	*/
static void ReverseString(char* _dest, char* _source)
{
	int i, length;
	length = strlen(_source);
	
	for (i = 0; i < length; ++i)
	{
		_dest[length-i-1] = _source[i];
	}
	
	_dest[i] = '\0';
}

