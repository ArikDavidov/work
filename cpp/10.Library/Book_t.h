#ifndef __BOOK_T_H__
#define __BOOK_T_H__


class Book_t
{
public:
	Book_t(const string _ISBN, const string _title, const string _author);
	virtual ~Book_t();

	string & GetISBN() const;
	string & GetTitle() const;
	string & GetAuthor() const;

private:
	Book_t(const Book_t& _book);
	Book_t & operator=(const  Book_t& _book);

private:
	string m_ISBN;
	string m_title;
	string m_author;
};

ostream& operator<<(ostream& _os, const Book_t& _book);


#endif /* __BOOK_T_H__ */

