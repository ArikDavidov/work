#ifndef __BIGNUMBER_T_H__
#define __BIGNUMBER_T_H__

#include <string>
using namespace std;


class BigNumber_t
{
public:
	BigNumber_t();
	BigNumber_t(const char* _str);
	BigNumber_t(const BigNumber_t& _str);
	BigNumber_t(const int _n);
	virtual~BigNumber_t();
	
	const BigNumber_t & operator=(const BigNumber_t& _str);
	const BigNumber_t & operator=(const int _n);

	const string & GetString() const;

private:
	bool IsNum(const char* _str) const;

private:
	string m_str;
};


inline const string & BigNumber_t::GetString() const
{
	return m_str;
}

ostream& operator<<(ostream& _os, const BigNumber_t& _bigNum);


#endif /* __BIGNUMBER_T_H__ */


	
