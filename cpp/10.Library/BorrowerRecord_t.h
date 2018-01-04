#ifndef __BORROWER_RECORD_T_H__
#define __BORROWER_RECORD_T_H__

#include "Borrower_t.h"

#include <list>
#include <string>
using namespace std;


class BorrowerRecord_t
{
public:
	BorrowerRecord_t(const string _ID, const string _name,
						const string _phoneNum);
	virtual ~BorrowerRecord_t();
	
	const Borrower_t* GetBorrower();

	bool HasBorrowedBooks() const;
	void AddBook(const string _ISBN);
	void RemoveBook(const string _ISBN);

private:
	BorrowerRecord_t(const BorrowerRecord_t& _borrowerRec);
	BorrowerRecord_t & operator=(const BorrowerRecord_t& _borrowerRec);

private:
	Borrower_t*  m_borrower;
	list<string> m_booksOnLoan;	// by ISBN
};


ostream& operator<<(ostream& _os, const BorrowerRecord_t& _borrowerRec);


#endif /* __BORROWER_RECORD_T_H__ */

