#ifndef __TEXCEPTION_T_H__
#define __TEXCEPTION_T_H__


class TException_t
{
public:
	__TEXCEPTION_T_H__(char* _object, char* _txt, char* _file, char* _line);
	virtual~TException_t ();

private:
	/* data */
};

TException_t(char* _object, char* _txt, char* _file, char* _line)
{
	cout << "constructor" << endl;
}

#endif /* __TEXCEPTION_T_H__ */

