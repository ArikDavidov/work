#ifndef PERSONAL_SAVING_IMPL_H
#define PERSONAL_SAVING_IMPL_H

#include "AccountImpl.h"


class PersonalSavingImpl : public AccountImpl
{
	friend class AccountFactory;
public:
	virtual ~PersonalSavingImpl()	{ cout << "~PersonalSavingImpl" << endl; }

    virtual void Update()
	{
		cout << "Personal Saving Account is informed" << endl;
	}

private:
	PersonalSavingImpl(const string& _type) {}
	
	PersonalSavingImpl(const PersonalSavingImpl&);
	PersonalSavingImpl& operator=(const PersonalSavingImpl&);
};


#endif // #ifndef PERSONAL_SAVING_IMPL_H


