#ifndef ACCOUNT_IMPL_H
#define ACCOUNT_IMPL_H

#include <iostream>
#include <string>


class AccountImpl
{
public:
	AccountImpl() {}
	virtual ~AccountImpl() {}

	virtual void Update() = 0;
};

#endif // #ifndef ACCOUNT_IMPL_H


