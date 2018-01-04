#ifndef __STRING_T_H__
#define __STRING_T_H__

#include "Buffer_t.h"

#include <iostream>
using namespace std;


class String_t : public Buffer_t
{
public:
	String_t(const char* _str = "");
	String_t(const String_t& _st);
	~String_t();
	
	const unsigned int Length() const; 
	const char* GetString() const;
	void SetString(const char* _str);
	String_t & operator=(const String_t& _st);
	
	String_t & operator+=(const String_t& _st);
	String_t & operator+=(const char* _str);
	
	bool operator<(const String_t& _st) const;
	bool operator>(const String_t& _st) const;
	bool operator>=(const String_t& _st) const;
	bool operator<=(const String_t& _st) const;
	bool operator==(const String_t& _st) const;
	bool operator!=(const String_t& _st) const;
		
	void Upper();
	void Lower();
	int  Compare(const String_t& _st) const;
	void Prepend(const String_t& _st);
	void Prepend(const char* _str);
	bool Contains(const String_t&) const;
	void Print() const;
	int FindFirst(char _char);
	int FindLast(char _char);
	String_t & operator()(int _start, unsigned int _len);

	static bool GetCaseSens();
	static bool SetCaseSens(bool _caseSene);
	
private:
	void CreateFrom(const char* _str);
	void SetTo(const char* _str, unsigned int _len);
	void Append(const char* _str, unsigned int _len);
	void InsertBefor(const char* _str, unsigned int _len);
	
private:
	static unsigned int m_numOfString_t;
	static bool m_caseSens;	
};

ostream& operator<<(ostream& _os, const String_t& _st);
istream& operator>>(istream& _is, String_t& _st);




#endif /* __STRING_T_H__ */



