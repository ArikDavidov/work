#ifndef __ANALYZER_T_H__
#define __ANALYZER_T_H__

#include <iostream>
#include <set>
using namespace std;

class Tokenizer_t;


class Analyzer_t
{
public:
	Analyzer_t(Tokenizer_t* _tokenizer);
	virtual ~Analyzer_t()	{}
	
	void Analyze(unsigned _lineNum);
	void Final();

protected:
	void CheckFirst(const string& _token, unsigned _lineNum);
	void CheckPredefinedType(const string& _token, unsigned _lineNum);
	void CheckIfElse(const string& _token, unsigned _lineNum);
	void CheckOperator(const string& _token, unsigned _lineNum);
	void CheckParentheses(const string& _token, unsigned _lineNum);
	void CheckUserDefined(const string& _token, unsigned _lineNum);
	
	bool IsPredefinedType(const string& _token) const;
	bool IsKeyWord(const string& _token) const;
	bool IsOperator(const string& _token) const;
	bool IsDelimiter(const string& _token) const;
	bool IsLegalName(const string& _token) const;

	
	void SetTokenFlsgsToZero();
	void Clear();
	
private:
	Analyzer_t(const Analyzer_t&);
	Analyzer_t & operator=(const Analyzer_t&);
	
private:
	Tokenizer_t* m_tokenizer;
	set<string>  m_types;
	set<string>  m_keyWords;
	set<string>  m_userDefined;
	bool m_isFirst;
	bool m_wasType;			// resets if current token is not Type
	int  m_plusCounter;		// resets if current token is not "+"
	int  m_minusCounter;	// resets if current token is not "-"
	
	int  m_ifCounter;
	int  m_parentheses;
	int  m_brakets;
	int  m_curlyBraces;
};
	

inline void Analyzer_t::SetTokenFlsgsToZero()
{
	m_wasType = false;
	m_plusCounter = 0;
	m_minusCounter = 0;
}

inline void Analyzer_t::Clear()
{
	m_userDefined.clear();

	m_isFirst = true;
	m_wasType = false;
	m_plusCounter = 0;
	m_minusCounter = 0;
	m_ifCounter = 0;
	m_parentheses = 0;
	m_brakets = 0;
	m_curlyBraces = 0;
}


#endif /* __ANALYZER_T_H__ */


