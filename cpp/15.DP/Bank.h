#ifndef __BANK_H__
#define __BANK_H__

#include "Subject.h"

#include <string>
using namespace std;

class Bank : public Subject
{ 
public: 
	virtual ~Bank();
	static Bank& CreateObj();
	
	void OpenAccount(const string& _type);
	
	void InvestInStockExchangeAccounts();
	void BonusToFamilyAccounts();
	void InviteSavingAccountOwners();

private: 
	Bank();
	Bank(const Bank&);
	void operator=(Bank&);

private: 
	static Bank m_bank;
};


#endif /* __BANK_H__ */



