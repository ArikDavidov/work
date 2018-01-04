#ifndef __BORROWER_T_H__
#define __BORROWER_T_H__

#include <map>
#include <string>
using namespace std;

class Borrower_t
{
public:
	Borrower_t(const string _ID, const string _name,
				const string _phoneNum);
	virtual ~Borrower_t();

	const string GetID() const;
	const string GetName() const;
	const string GetPhoneNum() const;

private:
	Borrower_t(const Borrower_t& _borrower);
	Borrower_t & operator=(const Borrower_t& _borrower);

private:
	string m_ID;
	string m_name;
	string m_phoneNum;
};


ostream& operator<<(ostream& _os, const Borrower_t& _borrower);


#endif /* __BORROWER_T_H__ */

