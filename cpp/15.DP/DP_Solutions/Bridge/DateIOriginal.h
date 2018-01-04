#ifndef DATEORIGINAL_H
#define DATEORIGINAL_H

#include <iostream>
#include <iomanip>
#include <string>


class Date {
public:
	Date( int day, int month ) { d = day;  m = month; }

	virtual void	tell()				{ ...};
	int				getDay() const		{ return d;}
	int				getMonth() const	{ return m;}
protected:
   int d, m;
};

#endif
