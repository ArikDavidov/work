#include "Tokenizer_t.h"

#include <iostream>
#include <cstddef>        // size_t
using namespace std;

const string Tokenizer_t::m_delimiters(" \t\r\n()[]{};<>=+-*&");
const string Tokenizer_t::m_blanks(" \t\r\n");


Tokenizer_t::Tokenizer_t()
{
	m_tokens = new vector<string>;
}

Tokenizer_t::~Tokenizer_t()
{
	delete m_tokens;
}

void Tokenizer_t::Tokenize(const string& _line)
{
    string token;
    size_t current = 0;
    size_t next = 0;
    
    m_tokens->clear();
    m_posNextGet = 0;
    
    for (;current < _line.size(); current = next)
    {        
		// SkipBlanks
		current = _line.find_first_not_of(m_blanks, current);
		if (current >= _line.size())
		{
			return;
		}
		
		next = _line.find_first_of(m_delimiters, current);
		if (current == next)	//if current is delimiter
		{
			++next;		// get only the delimiter
		}

		token = _line.substr(current, next - current);
        m_tokens->push_back(token);
    }
}
		// cout << token << endl;



