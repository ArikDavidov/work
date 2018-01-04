#ifndef __TOKENIZER_T_H__
#define __TOKENIZER_T_H__

#include <vector>
#include <string>

using namespace std;

class Tokenizer_t
{
public:
	Tokenizer_t();
	virtual ~Tokenizer_t();

	virtual void Tokenize(const string& _line);
	const string GetNext();

private:
	Tokenizer_t(const Tokenizer_t&);
	Tokenizer_t & operator=(const Tokenizer_t&);

private:
	vector<string>*          m_tokens;
	unsigned                 m_posNextGet;
	
	static const string      m_blanks;
	static const string      m_delimiters;
};



inline const string Tokenizer_t::GetNext()
{
	if (m_posNextGet >= m_tokens->size())
	{
		return "";
	}

	return m_tokens->at(m_posNextGet++);
}



#endif /* __TOKENIZER_T_H__ */



