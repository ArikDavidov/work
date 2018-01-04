#include "Bank.h"
#include "Account.h"


Bank Bank::m_bank;	// init static data


Bank& Bank::CreateObj()
{
	return m_bank;
}

Bank::Bank()
{
}

Bank::~Bank()
{
	for (Subject::iter_t it = m_observers.begin(); it != m_observers.end(); ++it)
	{
		delete it->second;
	}
}

void Bank::OpenAccount(const string& _type)
{
    new Account(_type, this);
}

void Bank::InvestInStockExchangeAccounts()
{
	Notify("PersonalSaving");
}

void Bank::BonusToFamilyAccounts()
{
	Notify("Family");
}

void Bank::InviteSavingAccountOwners()
{
	Notify("StockExchange");
}

