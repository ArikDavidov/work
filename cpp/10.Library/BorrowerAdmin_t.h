#ifndef __BORROWER_ADMIN_T_H__
#define __BORROWER_ADMIN_T_H__

#include "BorrowerRecord_t.h"

#include <map>
#include <vector>
#include <string>
using namespace std;


class BorrowerAdmin_t
{
public:
	BorrowerAdmin_t();
	virtual ~BorrowerAdmin_t();

	void  AddBorrower(const string _ID, const string _name, const string _phoneNum);
	const BorrowerRecord_t*           FindBorrowerByID(const string _ID) const;
	const vector<BorrowerRecord_t*> & FindBorrowerByName(const string _name) const;
	void  ReportOnAllBorrowers() const;
	void  RemoveBorrower(const string _ID);

private:
	BorrowerAdmin_t(const BorrowerAdmin_t& _borrower);
	BorrowerAdmin_t & operator=(const BorrowerAdmin_t& _borrower);

private:
	map<string, BorrowerRecord_t*>      m_borrowersByID;
	multimap<string, BorrowerRecord_t*> m_borrowersByName;
};




#endif /* __BORROWER_ADMIN_T_H__ */

