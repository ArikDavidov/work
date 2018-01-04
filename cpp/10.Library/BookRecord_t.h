#ifndef __BOOK_RECORD_T_H__
#define __BOOK_RECORD_T_H__

#include "Book_t.h"

#include <list>
#include <string>
using namespace std;


class BookRecord_t
{
public:
	BookRecord_t(const string _ISBN, const string _title,
				 const string _author, unsigned _numOfCopies);
	virtual ~BookRecord_t();

	const Book_t* GetBook() const;
	
	bool     IsBookAvailable() const;
	unsigned NumOfCopiesLoaned() const;
	unsigned TotalNumOfCopies() const;

	void AddBorrower(const string _ID);
	void RemoveBorrower(const string _ID);

private:
	BookRecord_t(const BookRecord_t& _bookRec);
	BookRecord_t & operator=(const BookRecord_t& _bookRec);

private:
	Book_t*      m_book;
	unsigned     m_numOfCopies;
	list<string> m_borrowers;	//by ID
	list<string> m_waitingList;	//by ID
};


ostream& operator<<(ostream& _os, const BookRecord_t& _bookRec);


#endif /* __BOOK_RECORD_T_H__ */

