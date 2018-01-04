#include "AccountFactory.h"

#include "PersonalSavingImpl.h"
#include "FamilyImpl.h"
#include "StockExchangeImpl.h"

#include <string>
using namespace std;


AccountImpl* AccountFactory::CreateAccount(const string& _type)
{
	AccountImpl* ptrAccount = 0;
	
	if (_type == "PersonalSaving")
	{
		ptrAccount = new PersonalSavingImpl("PersonalSaving");
	}
	if (_type == "Family")
	{
		ptrAccount = new FamilyImpl("Family");
	}
	if (_type == "StockExchange")
	{
		ptrAccount = new StockExchangeImpl("StockExchange");
	}
	
	return ptrAccount;
}


