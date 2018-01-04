/*#include "Parser.h"*/
#include "CDR.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>		/* getpid */
#include <unistd.h>			/* getpid */

#define SUCCESS			0
#define FAILUERE		1

#define CALL_TYPE_LEN 	6
#define CDR_FORMAT	"%[^|]%*c%[^|]%*c%[^|]%*c%[^|]%*c%[^|]%*c%[^|]%*c%[^|]%*c%[^|]%*c%u|%lf|%lf|%[^|]%*c%[^\n]"


static CallType GetCallType(char* _buf)
{
	char* lut[] = {"MOC", "MTC", "SMS-MO", "SMS-MT", "GPRS"};
	int i;
	
	/*printf("%s\n", _buf);*/
	for (i = 0; i < sizeof(lut) / sizeof(char*); ++i)
	{
		if (0 == strcmp(_buf, lut[i]))
		{
			return (CallType)i;
		}
	}
	
	return -1;
}

int Parse(char* _line, Cdr* _cdr)
{
	char tempCallType[CALL_TYPE_LEN + 1];

	if (!_line || !_cdr)
	{
		return FAILUERE;
	}

	sscanf(_line, CDR_FORMAT,  
			_cdr->m_imsi, _cdr->m_msisdn, _cdr->m_imei, _cdr->m_operatorBrandName, _cdr->m_mccMnc,
			tempCallType, _cdr->m_callDate, _cdr->m_callTime, &_cdr->m_duration, &_cdr->m_download,
			&_cdr->m_upload, _cdr->m_partyMsisdn, _cdr->m_partyOperator);			
	
	_cdr->m_callType = GetCallType(tempCallType);
	assert(-1 != _cdr->m_callType);


	_cdr->m_duration = (unsigned int)getpid();
	/*
	CdrPrint(_cdr);
	*/

	return SUCCESS;
}


/*
int main()
{
	char line[] = LINE;
	Cdr cdr = {0};

	Parse(line, &cdr);

	return 0;
}

	sscanf(line, CDR_FORMAT,  
			cdr.m_imsi, cdr.m_msisdn, cdr.m_imei, cdr.m_operatorBrandName, cdr.m_mccMnc,
			tempCallType, cdr.m_callDate, cdr.m_callTime, &cdr.m_duration, &cdr.m_download,
			&cdr.m_upload, cdr.m_partyMsisdn, cdr.m_partyOperator);			
	
	char s[64];
	cdr.m_callType = GetCallType(tempCallType);
	assert(-1 != cdr.m_callType);
	CdrPrint(&cdr);

	sscanf("this is a test\n", "%s", s);
	printf("%s\n", s);
	sscanf("this is a test\n", "%[^\n]", s);
	printf("%s\n", s);
	sscanf("this is a test\n", "%*s%s", s);
	printf("%s\n", s);
	sscanf("this is a test\n", "%2s", s);
	printf("%s\n", s);
	sscanf("this is a test\n", "%10s", s);
	printf("%s\n", s);
	sscanf("this is a test\n", "%*3s%s", s);
	printf("%s\n", s);
	sscanf("this is a test\n", "%*s%s", s);
	printf("%s\n", s);
*/

