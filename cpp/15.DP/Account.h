#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Observer.h"

#include <string>
using namespace std;

class AccountImpl;



class Account : public Observer
{
public:
	~Account();										// detach from bank
	Account(const string& _type, Subject* _bank);	// attach to bank
	
    virtual void Update(Subject* _subject);

protected:
	AccountImpl*  m_account;
	string        m_type;
};



#endif // #ifndef ACCOUNT_H
