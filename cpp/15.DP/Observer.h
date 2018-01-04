#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <iostream>

using namespace std;


class Subject;

class Observer
{
public:
	virtual ~Observer() {}
    virtual void Update(Subject* _subject) = 0;
    
protected:
	Observer() {}

protected:
	Subject* m_bank;
};


#endif /* __OBSERVER_H__ */


