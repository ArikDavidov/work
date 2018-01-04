#ifndef __TCONTAINER_T_H__
#define __TCONTAINER_T_H__

#include <vector>
#include <list>
#include <algorithm>    // find_if
#include <typeinfo>
using namespace std;



template <typename T, class Container>
class tContainer_t
{
	typedef typename Container::iterator iter_t;
	typedef typename Container::const_iterator const_iter_t;

public:
	tContainer_t() {}
	virtual ~tContainer_t() {}
	
	void push_back(const T* _p)	{ m_container.push_back((T*)_p); }
	unsigned size() const		{ return m_container.size(); }
	bool empty() const			{ return m_container.begin() == m_container.end(); }
	T* front()					{ return m_container.empty() ? 0 : m_container.front(); }
	T* back()					{ return m_container.empty() ? 0 : m_container.back(); }
	void clear()				{ m_container.clear(); }	//remove all elements
	
	T* find(const T& _element) const;
	T* remove(const T& _element);
	void RemoveAndDelete(const T& _element);
	void RemoveAndDeleteAll();

	T* operator[](unsigned _i);
	const T* operator[](unsigned _i) const;	
	
private:

	iter_t begin() 				{ return m_container.begin(); }
	const_iter_t begin() const	{ return m_container.begin(); }
	iter_t end()   				{ return m_container.end(); }
	const_iter_t end() const	{ return m_container.end(); }
	
	tContainer_t(const Container& _container) {}
	Container & operator=(const Container& _container);

	struct Equals {
		Equals(const T& _element) : val(_element) {}
		bool operator()(T* _param) const { return *_param == val; }
		const T val;
	};

private:
	Container m_container;
};


template <typename T, class Container>
T* tContainer_t<T, Container>::find(const T& _element) const
{
	const_iter_t it = find_if(begin(), end(), Equals(_element));
	return it == end() ? 0 : *it;
}

//{ T* ret = find(_element); remove (begin(), end(), ret); return ret; }
template <typename T, class Container>
T* tContainer_t<T, Container>::remove(const T& _element)
{
	iter_t it = find_if(begin(), end(), Equals(_element));
	if (it == end())
	{
		return 0;
	}
	
	m_container.erase(it);
	
	return *it;
}

template <typename T, class Container>
void tContainer_t<T, Container>::RemoveAndDelete(const T& _element)
{
	T* ep = remove(_element);
	if (0 == ep)
	{
		return;
	}

	delete ep;
}

template <typename T, class Container>
void tContainer_t<T, Container>::RemoveAndDeleteAll()
{
	for (int i = 0; i < size(); ++i)
	{
		delete m_container[i];
	}

	clear();
}

template <typename T, class Container>
const T* tContainer_t<T, Container>::operator[](unsigned _i) const
{
	if (_i >= m_container.size())
	{
		return 0;
	}
	
	if (typeid(Container) == typeid(list<T*>))
	{
		const_iter_t it = begin();
		for (unsigned j = 0; j < _i; ++j)
		{
			++it;
		}
		
		return *it;
	}
	
	return (*((vector<T*>*)&m_container))[_i];
}

template <typename T, class Container>
T* tContainer_t<T, Container>::operator[](unsigned _i)
{
	if (_i >= m_container.size())
	{
		return 0;
	}
	
	if (typeid(Container) == typeid(list<T*>))
	{
		iter_t it = begin();
		for (unsigned j = 0; j < _i; ++j)
		{
			++it;
		}
		
		return *it;
	}
	
	return (*((vector<T*>*)&m_container))[_i];
}


#endif /* __TCONTAINER_T_H__ */







