#include "Analyzer_t.h"
#include "Tokenizer_t.h"

#include <iostream>
#include <string>
#include <cstring>
#include <set>
using namespace std;


Analyzer_t::Analyzer_t(Tokenizer_t* _tokenizer)
: m_isFirst(true)
{
	if(!_tokenizer)
	{
		return;
	}

	m_tokenizer = _tokenizer;
	
	const string types[] = {"char", "short", "int", "long", "float", "double", "void"};
	set<string> a(types, types + 7);
	m_types = a;

	const string keyWords[] = {"if", "else", "for" , "while", "class", "private",
								 "public", "protected", "main", "const", "virtual"};
	set<string> b(keyWords, keyWords + 11);
	m_keyWords = b;
}

void Analyzer_t::Analyze(unsigned _lineNum)
{
	string token;
	while ((token = m_tokenizer->GetNext()) != "")
	{
		CheckFirst(token, _lineNum);

		if (IsPredefinedType(token))
		{
			CheckPredefinedType(token, _lineNum);
		}
		else if (IsKeyWord(token))
		{
			CheckIfElse(token, _lineNum);
		}
		else if (IsOperator(token))
		{
			CheckOperator(token, _lineNum);
		}
		else if (IsDelimiter(token))
		{
			CheckParentheses(token, _lineNum);
		}
		else
		{
			CheckUserDefined(token, _lineNum);
		}
	}
}

void Analyzer_t::CheckFirst(const string& _token, unsigned _lineNum)
{
	if (m_isFirst)
	{
		m_isFirst = false;
	
		if (_token != "main")
		{
			cout << "line " << _lineNum << ": " << "declaration before 'main'" << endl;
	 	}
	}
}

bool Analyzer_t::IsPredefinedType(const string& _token) const
{
	return m_types.find(_token) != m_types.end();
}

bool Analyzer_t::IsKeyWord(const string& _token) const
{
	return m_keyWords.find(_token) != m_keyWords.end();
}

bool Analyzer_t::IsOperator(const string& _token) const
{
	// "++--==->=+-*&<<>>"
	return string::npos != _token.find_first_of("+-=*&<>");
}

bool Analyzer_t::IsDelimiter(const string& _token) const
{
	return string::npos != _token.find_first_of("()[]{};<>=+-*&");
}

void Analyzer_t::CheckPredefinedType(const string& _token, unsigned _lineNum)
{
	if (m_wasType)
	{
		m_wasType = false;
		cout << "line " << _lineNum << ": " << "multiple type" << endl;
	}
	else
	{
		SetTokenFlsgsToZero();
		m_wasType = true;
	}
}


void Analyzer_t::CheckIfElse(const string& _token, unsigned _lineNum)
{
	if (_token == "if")
	{
		++m_ifCounter;
	}
	else if (_token == "else")
	{
		--m_ifCounter;
		if (m_ifCounter < 0)
		{
			m_ifCounter = 0;
			cout << "line " << _lineNum << ": " << "else withot if" << endl;
		}
	}

	SetTokenFlsgsToZero();
}

void Analyzer_t::CheckOperator(const string& _token, unsigned _lineNum)
{
	if (_token == "+")
	{
		if (2 == m_plusCounter)
		{
			m_plusCounter = 0;
			cout << "line " << _lineNum << ": " << "no operator +++" << endl;
		}
		else if (0 == m_plusCounter)
		{
			SetTokenFlsgsToZero();
			++m_plusCounter;
		}
		else
		{
			++m_plusCounter;
		}
	}
	else if (_token == "-")
	{
		if (2 == m_minusCounter)
		{
			m_minusCounter = 0;
			cout << "line " << _lineNum << ": " << "no operator ---" << endl;
		}
		else if (0 == m_minusCounter)
		{
			SetTokenFlsgsToZero();
			++m_minusCounter;
		}
		else
		{
			++m_minusCounter;
		}
	}
}

void Analyzer_t::CheckParentheses(const string& _token, unsigned _lineNum)
{
	if (_token == "(")
	{
		++m_parentheses;
	}
	else if (_token == ")")
	{
		--m_parentheses;
		if (m_parentheses < 0)
		{
			m_parentheses = 0;
			cout << "line " << _lineNum << ": " << ") withot (" << endl;
		}
	}
	else if (_token == "[")
	{
		++m_brakets;
	}
	else if (_token == "]")
	{
		--m_brakets;
		if (m_brakets < 0)
		{
			m_brakets = 0;
			cout << "line " << _lineNum << ": " << "] withot [" << endl;
		}
	}
	else if (_token == "{")
	{
		++m_curlyBraces;
	}
	else if (_token == "}")
 	{
		--m_curlyBraces;
		if (m_curlyBraces < 0)
		{
			m_curlyBraces = 0;
			cout << "line " << _lineNum << ": " << "} withot {" << endl;
 		}
	}
	
	SetTokenFlsgsToZero();
}

void Analyzer_t::CheckUserDefined(const string& _token, unsigned _lineNum)
{
	if (m_wasType)
	{
		if(m_userDefined.find(_token) == m_userDefined.end())
		{
			if (IsLegalName(_token))
			{
				m_userDefined.insert(_token);				
			}
			else
			{
				cout << "line " << _lineNum << ": " << "illegal variable name" << endl;
			}
		}
		else
		{
			cout << "line " << _lineNum << ": " << "variable " << _token << " already declared" << endl;
		}
	}
	else
	{
		if(m_userDefined.find(_token) == m_userDefined.end())
		{
			cout << "line " << _lineNum << ": " << _token << " isn't defined" << endl;
		}
	}

	SetTokenFlsgsToZero();
}

bool Analyzer_t::IsLegalName(const string& _token) const
{
	if (!isalpha(_token[0]) && strcmp("_", &_token[0]))
	{
		return false;
	}

	for (unsigned i = 1; i < _token.size(); ++i)
	{
		if (!isalnum(_token[i]) && strcmp("_", &_token[i]))
		{
			return false;
		}
	}

	return true;
}

void Analyzer_t::Final()
{	
 	if (m_parentheses > 0)
	{
		cout << m_parentheses << " unclosed (" << endl;
	}
	if (m_brakets > 0)
	{
		cout << m_brakets << " unclosed [" << endl;
	}
	if (m_curlyBraces > 0)
	{
		cout << m_curlyBraces << " unclosed {" << endl;
	}
	
	Clear();
}
 	
 	
 	

