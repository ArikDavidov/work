#ifndef __BOOK_ADMIN_T_H__
#define __BOOK_ADMIN_T_H__

#include "BookRecord_t.h"

#include <map>
#include <vector>

class BookAdmin_t
{
public:
	BookAdmin_t();
	virtual ~BookAdmin_t();

	void AddBook(const string _ISBN, const string _title,
					const string _author, const string _nCopies);
	void RemoveBook(const string _ISBN);
	
	const BookRecord_t*           FindBookByISBN(const string _ISBN) const;
	const vector<BookRecord_t*> & FindBookByTitle(const string _title) const;
	const vector<BookRecord_t*> & FindBookByAuthor(const string _author) const;

private:
	BookAdmin_t(const BookAdmin_t& _bookAdmin);
	BookAdmin_t & operator=(const  BookAdmin_t& _bookAdmin);

private:
	map<string, BookRecord_t>       m_booksByISBN;
	multimap<string, BookRecord_t>  m_booksByTitle;
	multimap<string, BookRecord_t>  m_booksByAuthor;
};




#endif /* __BOOK_ADMIN_T_H__ */

