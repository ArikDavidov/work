#ifndef STOCK_EXCHANGE_IMPL_H
#define STOCK_EXCHANGE_IMPL_H

#include "AccountImpl.h"


class StockExchangeImpl : public AccountImpl
{
	friend class AccountFactory;
public:
	virtual ~StockExchangeImpl()	{ cout << "~StockExchangeImpl" << endl; }

    virtual void Update()
	{ 
		cout << "Stock Exchange Account is informed" << endl;
	}

private:
	StockExchangeImpl(const string& _type) {}
	
	StockExchangeImpl(const StockExchangeImpl&);
	StockExchangeImpl& operator=(const StockExchangeImpl&);
};


#endif // #ifndef STOCK_EXCHANGE_IMPL_H


