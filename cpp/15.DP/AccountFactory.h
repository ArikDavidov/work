#ifndef ACCOUNT_FACTORY_H
#define ACCOUNT_FACTORY_H

#include "Account.h"

#include <string>

using namespace std;

class PersonalSavingImpl;
class FamilyImpl;
class StockExchangeImpl;


class AccountFactory
{
public:
	static AccountImpl* CreateAccount(const string& _type);

private:
	~AccountFactory();
	AccountFactory();
};



#endif // #ifndef ACCOUNT_FACTORY_H


