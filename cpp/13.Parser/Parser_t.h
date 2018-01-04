#ifndef __PARSER_T_H__
#define __PARSER_T_H__

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Tokenizer_t;
class Analyzer_t;


class Parser_t
{
public:
	Parser_t();
	virtual ~Parser_t();
	
	virtual void Parse(const string& _path);
	
private:
	Parser_t(const Parser_t&);
	Parser_t& operator=(const Parser_t&);

private:
	Tokenizer_t* m_tokenizer;
	Analyzer_t*  m_analyzer;
};



#endif /* __PARSER_T_H__ */












