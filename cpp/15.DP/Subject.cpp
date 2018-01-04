#include "Subject.h"
#include "Observer.h"

#include <iostream>
#include <map>
using namespace std;



void Subject::Attach(const string& _type, Observer* _observer)
{ 
	if (m_observers.end() != FindObserver(_type, _observer))
	{
		cerr << "already exist" << endl;
		return;
	}
	
	m_observers.insert(pair<string, Observer*>(_type, _observer));
} 

void Subject::Detach(const string& _type, Observer* _observer)
{ 
	iter_t it = FindObserver(_type, _observer);
	if (m_observers.end() == it)
	{
		cerr << "observer not found" << endl;
		return;
	}
	
	m_observers.erase(it);
}

//Subject::iter_t Subject::FindObserver(const string& _type, Observer* _observer)
//{ 
//	iter_t it = m_observers.find(_type);
//	for (; it != m_observers.end() && it->first == _type; ++it)
//	{
//		if (it->second == _observer)
//		{
//			return it;
//		}
//	}
//	
//	return m_observers.end();
//}

Subject::iter_t Subject::FindObserver(const string& _type, Observer* _observer)
{ 
    pair<iter_t, iter_t> range = m_observers.equal_range(_type);
    for (iter_t it = range.first; it != range.second; ++it)
	{
		if (it->second == _observer)
		{
			return it;
		}
	}
	
	return m_observers.end();
}

//void Subject::Notify(const string& _type)
//{ 
//	iter_t it = m_observers.find(_type);
//	for (; it != m_observers.end() && it->first == _type; ++it)
//	{
//		(it->second)->Update(this);
//	}
//}

void Subject::Notify(const string& _type)
{
    pair<iter_t, iter_t> range = m_observers.equal_range(_type);
    for (iter_t it = range.first; it != range.second; ++it)
	{
		it->second->Update(this);
	}
}




