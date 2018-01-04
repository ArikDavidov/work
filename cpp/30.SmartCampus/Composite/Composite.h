#ifndef __COMPOSITE_H__
#define __COMPOSITE_H__

#include <vector>
#include <algorithm>    // find
#include <tr1/memory>
#include <stdexcept>


namespace smartcampus
{


template<typename T>
class Composite : public T
{
public:
	virtual ~Composite();
	
	void AddChild(std::tr1::shared_ptr<T> _child);
	void RemoveChild(std::tr1::shared_ptr<T> _child);

protected:  // private?
	std::vector<std::tr1::shared_ptr<T> > m_children;
};


template<typename T>
Composite<T>::~Composite()
{
}

template<typename T>
void Composite<T>::AddChild(std::tr1::shared_ptr<T> _child)
{
	typename std::vector<std::tr1::shared_ptr<T> >::iterator it;
	
    it = find(m_children.begin(),m_children.end(),_child);
	if (it != m_children.end())
	{
	    throw std::runtime_error("AddChild failed: child already exists");
	}

	m_children.push_back(_child);
}

template<typename T>
void Composite<T>::RemoveChild(std::tr1::shared_ptr<T> _child)
{
	typename std::vector<std::tr1::shared_ptr<T> >::iterator it;
	
	it = find(m_children.begin(),m_children.end(),_child);
	if (it == m_children.end())
	{
	    throw std::runtime_error("RemoveChild failed: child was not found");
	}

	m_children.erase(it);
}

    
    
    
    
}  // namespace smartcampus

#endif // __COMPOSITE_H__








