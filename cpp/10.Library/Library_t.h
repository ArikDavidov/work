#ifndef __LIBRARY_T_H__
#define __LIBRARY_T_H__

// #include "BorrowerAdmin_t.h"
// #include "BookAdmin_t.h"

#include <string>
using namespace std;

class BorrowerAdmin_t;
class BookAdmin_t;

class Library_t
{
public:
	Library_t();
	virtual ~Library_t();

	void BorrowBook(const string _ID, const string _ISBN);	// throws exception
	void ReturnBook(const string _ID, const string _ISBN);	// throws exception

private:
	Library_t(const Library_t& _library);
	Library_t & operator=(const  Library_t& _library);

private:
	BookAdmin_t*     m_bookAdmin;		// new..
	BorrowerAdmin_t* m_borrowerAdmin;	// new..
};



#endif /* __LIBRARY_T_H__ */

