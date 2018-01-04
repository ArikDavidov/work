#ifndef __TTCONTAINER_T_H__
#define __TTCONTAINER_T_H__

#include <vector>
#include <list>
#include <algorithm>    //find_if
#include <typeinfo>
using namespace std;



template <typename T, template <typename, typename alloc = allocator<T> > class Container>
class tContainerTow_t
{
	typedef typename ContainerTow<T>::iterator iter_t;
	typedef typename ContainerTow<T, std::allocator<T> >::const_iterator const_iter_t;

public:
	tContainerTow_t() {}
	virtual ~tContainerTow_t() {}
	
	void push_back(const T* _p)	{ m_container.push_back((T*)_p); }
	unsigned size() const		{ return m_container.size(); }
	bool empty() const			{ return m_container.begin() == m_container.end(); }
	T* front()					{ return m_container.empty() ? 0 : m_container.front(); }
	T* back()					{ return m_container.empty() ? 0 : m_container.back(); }
	void clear()				{ m_container.clear(); }	//remove all elements

	iter_t begin() 				{ return m_container.begin(); }
	const_iter_t begin() const	{ return m_container.begin(); }
	iter_t end()   				{ return m_container.end(); }
	const_iter_t end() const	{ return m_container.end(); }
	
	T* find(const T& _element) const;
	T* remove(const T& _element);
	void RemoveAndDelete(const T& _element);
	void RemoveAndDeleteAll();

	T* operator[](unsigned _i);
	const T* operator[](unsigned _i) const;	
	
private:
	tContainerTow_t(const ContainerTow<T, std::allocator<T> > & _container) {}
	ContainerTow<T, std::allocator<T> > & operator=(const ContainerTow<T, std::allocator<T> >& _container);

	struct Equals {
		Equals(const T& _element) : val(_element) {}
		bool operator()(T* _param) const { return *_param == val; }
		const T val;
	};

private:
	ContainerTow<T, std::allocator<T> > m_container;
};


template <typename T, template <typename, typename> class ContainerTow>
T* tContainerTow_t<T, ContainerTow>::find(const T& _element) const
{
	const_iter_t it = find_if(begin(), end(), Equals(_element));
	return it == end() ? 0 : *it;
}

//{ T* ret = find(_element); remove (begin(), end(), ret); return ret; }
template <typename T, template <typename, typename> class ContainerTow>
T* tContainerTow_t<T, ContainerTow>::remove(const T& _element)
{
	iter_t it = find_if(begin(), end(), Equals(_element));
	if (it == end())
	{
		return 0;
	}
	
	m_container.erase(it);
	
	return *it;
}

template <typename T, template <typename, typename> class ContainerTow>
void tContainerTow_t<T, ContainerTow>::RemoveAndDelete(const T& _element)
{
	T* ep = remove(_element);
	if (0 == ep)
	{
		return;
	}

	delete ep;
}

template <typename T, template <typename, typename> class ContainerTow>
void tContainerTow_t<T, ContainerTow>::RemoveAndDeleteAll()
{
	for (int i = 0; i < size(); ++i)
	{
		delete m_container[i];
	}

	clear();
}

template <typename T, template <typename, typename> class ContainerTow>
const T* tContainerTow_t<T, ContainerTow>::operator[](unsigned _i) const
{
	if (_i >= m_container.size())
	{
		return 0;
	}
	
	if (typeid(ContainerTow<T, std::allocator<T> >) == typeid(list<T*>))
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

template <typename T, template <typename, typename> class ContainerTow>
T* tContainerTow_t<T, ContainerTow>::operator[](unsigned _i)
{
	if (_i >= m_container.size())
	{
		return 0;
	}
	
	if (typeid(ContainerTow<T, std::allocator<T> >) == typeid(list<T*>))
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


#endif /* __TTCONTAINER_T_H__ */








template <typename, typename> 
