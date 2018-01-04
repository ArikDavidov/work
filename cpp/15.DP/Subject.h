#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <map>
#include <string>

using namespace std;

class Observer;

class Subject
{
public:
	typedef multimap<string, Observer*>::iterator iter_t;
	
	virtual ~Subject() {}

    virtual void Attach(const string& _type, Observer* _observer);
    virtual void Detach(const string& _type, Observer* _observer);

protected:
	Subject() {}
	virtual void Notify(const string& _type);
	
	iter_t FindObserver(const string& _type, Observer* _observer);
	
protected:
    multimap<string, Observer*> m_observers;
};


#endif /* __SUBJECT_H__ */


