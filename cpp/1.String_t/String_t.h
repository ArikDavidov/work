#ifndef __STRING_T_H__
#define __STRING_T_H__

#include <iostream>
using namespace std;

class String_t
{
public:
	//String_t();
	~String_t();
	String_t(const char* _str = "");
	String_t(const String_t& _st);
	const unsigned int Length() const; //{return m_len;}
	inline const char* GetString() const; //{return m_str;}
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
	
	const char operator[](const unsigned int _i) const;
	char & operator[](const unsigned int _i);
	
	void Upper();
	void Lower();
	int  Compare(const String_t& _st) const;
	void Prepend(const String_t& _st);
	void Prepend(const char* _str);
	bool Contains(const String_t&) const;
	void Print() const;
	static bool GetCaseSens(); //{return m_caseSens;}
	static bool SetCaseSens(bool _caseSene);
	static unsigned int GetDefaultCapacity(); //{return m_defaultCapacity;}
	static unsigned int SetDefaultCapacity(unsigned int _defaultCapacity);
	int FindFirst(char _char);
	int FindLast(char _char);
	String_t & operator()(int _start, unsigned int _len);
	
private:
	void CreateFrom(const char* _str);
	void SetTo(const char* _str, unsigned int _len);
	void Append(const char* _str, unsigned int _len);
	void InsertBefor(const char* _str, unsigned int _len);
	
private:
	char* m_str;
	unsigned int m_len;
	unsigned int m_capacity;
	
	static unsigned int m_defaultCapacity;
	static unsigned int m_numOfString_t;
	static bool m_caseSens;
	
	//static const unsigned int MAGIC = 0xBA123456;
};

ostream& operator<<(ostream& _os, const String_t& _st);
istream& operator>>(istream& _is, String_t& _st);



inline const char* String_t::GetString() const
{
	return m_str;
}


/*
static unsigned int GetDefaultCapacity() 
{
	return m_defaultCapacity;
}
static bool String::GetCaseSens()
{
	return m_caseSens;
}
inline const char* String_t::GetString() const
{
	return m_str;
}
inline unsigned int String_t::Length() const
{
	return m_len;
}
*/


#endif /* __STRING_T_H__ */



