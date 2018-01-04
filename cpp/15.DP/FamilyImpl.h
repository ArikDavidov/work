#ifndef FAMILY_IMPL_H
#define FAMILY_IMPL_H

#include "AccountImpl.h"


class FamilyImpl : public AccountImpl
{
	friend class AccountFactory;
public:
	virtual ~FamilyImpl()	{ cout << "~FamilyImpl" << endl; }

    virtual void Update()
	{
		cout << "Family Account got the bonus" << endl;
	}

private:
	FamilyImpl(const string& _type)	{}
	
	FamilyImpl(const FamilyImpl&);
	FamilyImpl& operator=(const FamilyImpl&);
};


#endif // #ifndef FAMILY_IMPL_H


