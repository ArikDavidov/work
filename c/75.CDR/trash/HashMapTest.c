#include "Operators.h"
#include "OperatorTotals.h"
#include "MsgTransport.h"
#include "HashMap.h"
#include "CDR.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>	/* link with -pthread */
#include <assert.h>


static size_t OperatorsHashFunc(const void* _key)
{
	int sum;
	char* str = (char*)_key;
	
	assert(_key);
	
	for (sum = 0; '\0' != str[0]; ++str)
	{
		sum += (int)str[0];
	}
	
	return (size_t)sum;
}

static int OperatorsKeysEqualFunc(const void* _firstKey, const void* _secondKey)
{
	assert(_firstKey);
	assert(_secondKey);
	
	printf("_firstKey: %s\n", (char*)_firstKey);
	printf("_secondKey: %s\n", (char*)_secondKey);

	return !strcmp((char*)_firstKey, (char*)_secondKey);
}

static void* KeyCreate(const char* _mccMnc)
{
	void* key;
	
	assert(_mccMnc);
	
	key = malloc(7 + sizeof(char));
	if (!key)
	{
		return NULL;
	}
	
	strcpy(key, _mccMnc);
	
	return key;
} 

static void CdrPrint(const Cdr* _cdr)
{
	printf("\n***********************   CDR   ***********************\n");
	printf("IMSI: %s,\t", _cdr->m_imsi);
	printf("IMSI: %s,\t\n", _cdr->m_imsi);
	printf("MSISDN: %s,\t", _cdr->m_msisdn);
	printf("IMEI: %s,\t\n", _cdr->m_imei);
	printf("%s,\t", _cdr->m_operatorBrandName);
	printf("mccMnc: %s,\t\n", _cdr->m_mccMnc);
	printf("testCallType: %d,\n", _cdr->m_callType);
	printf("%s, ", _cdr->m_callDate);
	printf("%s,\t", _cdr->m_callTime);
	printf("duration: %d,\t\n", _cdr->m_duration);
	printf("download: %d,\t", _cdr->m_download);
	printf("upload: %d,\t\n", _cdr->m_upload);
	printf("partyMsisdn: %s,\t", _cdr->m_partyMsisdn);
	printf("partyOperator: %s\t", _cdr->m_partyOperator);
	printf("\n\n");
}

int main()
{
	OperatorTotals* operator = NULL;
	OperatorTotals* item = NULL;
	void* key;
	size_t i = 0;
	HashMap* map = NULL;
	MapResult ret;
	Cdr cdr= {"123451234512345", "+972542151110", "42424242442666",
							"Ariel Telecom Israel", "42508", SMS_MT, "12/9/17", "19:14",
							42, 700, i, "+972542151111","42508"};

	assert(operator = OperatorTotalsCreate());
		
	assert(key = KeyCreate(cdr.m_mccMnc));
	
	map = HashMapCreate(50000, (HashFunction)OperatorsHashFunc,
										 OperatorsKeysEqualFunc);
	
	HashMapInsert(map, key, (void*)operator);

	ret = HashMapFind(map, (void*)cdr.m_mccMnc, (void**)&item);
	printf("%d\n", ret);
	OperatorTotalsPrint(item);
	CdrPrint(&cdr);

	return 0;
}








