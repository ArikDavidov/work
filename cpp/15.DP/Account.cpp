#include "Account.h"
#include "Subject.h"
#include "AccountImpl.h"
#include "AccountFactory.h"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


Account::Account(const string& _type, Subject* _bank)
: m_type(_type)
{
	m_account = AccountFactory::CreateAccount(_type);
	m_bank = _bank;
	m_bank->Attach(_type, this);
}

Account::~Account()
{
	m_bank->Detach(m_type, this);
	
	delete m_account;	// delete implementation creted by Factory
	m_account = 0;
}

void Account::Update(Subject* _subject)
{
	if (_subject != m_bank)
	{
		cerr << "Account::Update error" << endl;
		return;
	}
	
	m_account->Update();
}



