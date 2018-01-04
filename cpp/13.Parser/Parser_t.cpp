#include "Parser_t.h"
#include "Tokenizer_t.h"
#include "Analyzer_t.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;


Parser_t::Parser_t()
{
    m_tokenizer = new Tokenizer_t;
    m_analyzer = new Analyzer_t(m_tokenizer);
}
    
Parser_t::~Parser_t()
{
    delete m_tokenizer;
    delete m_analyzer;
}   
    
void Parser_t::Parse(const string& _path)
{
    ifstream infile(_path.c_str());
    if(!infile)
    {  
        cout << "File opening failed\n";
        return; // TODO  throw exception?
    }
    
    string line;
    for (unsigned lineNum = 1;; ++lineNum)
    {
        getline(infile, line);
        if (infile.fail())
        {
            break;
        }
        
        m_tokenizer->Tokenize(line);
        m_analyzer->Analyze(lineNum);
    }
    
    m_analyzer->Final();
}














