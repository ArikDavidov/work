#ifndef __VECTOR_T_H__
#define __VECTOR_T_H__

#include "Container_t.h"

#include <iostream>
using namespace std;


template <typename V>
class Vector_t : public Container_t <V>
{
public:
	Vector_t(int _capacity = 32, int _blockSize = 16);
	virtual ~Vector_t();
	
	//int  Count(V _element);
	//bool IsEmpty(V* _element);
	
	virtual void Append(const V* _element, int _i);
	virtual void Prepend(const V* _element, int _i);
	virtual bool Contains(const V& _element) const;
	virtual V*   Find(const V& _element) const;
	virtual int  Index(const V& _element) const;
	virtual void Insert(const V* _element);
	virtual void Remove(const V& _element);
	virtual void RemoveAll();
	virtual void RemoveAndDelete(const V& _element);
	virtual void RemoveAndDeleteAll();
	
private:
	V** m_vec;
	int m_capacity;
	int m_blockSize;
};




template <typename V>
Vector_t<V>::Vector_t(int _capacity, int _blockSize)
: m_capacity(_capacity), m_blockSize(_blockSize)
{
	m_vec = new V*[m_capacity];
	
	cout << "m_capacity:  " << m_capacity  << endl;
	cout << "m_blockSize: " << _blockSize  << endl;
	cout << "m_noe:       " << this->m_noe << endl;
}


template <typename V>
void Vector_t<V>::Append(const V* _element, int _i)
{
	if (!_element)
	{
		return;
	}
	
	//TODO GrowIfNeeded
	//TODO right shift
	
	m_vec[_i + 1] = (V*)_element;
	++this->m_noe;
	cout << "m_noe: " << this->m_noe << endl;
}

template <typename V>
void Vector_t<V>::Prepend(const V* _element, int _i)
{
	if (!_element)
	{
		return;
	}
	
	//TODO GrowIfNeeded
	//TODO right shift
	
	m_vec[_i] = (V*)_element;
	++this->m_noe;
}

template <typename V>
bool Vector_t<V>::Contains(const V& _element) const
{
	return (-1 != Index(_element)) ? true : false;
}

template <typename V>
V* Vector_t<V>::Find(const V& _element) const
{
	int i = Index(_element);
	return (-1 != i) ? m_vec[i] : NULL;
}

template <typename V>
int Vector_t<V>::Index(const V& _element) const
{
	for (int i = 0; i < this->m_noe; ++i)
	{
		if (m_vec[i] == _element)
		{
			return i;
		}
	}
		
	return -1;
}

template <typename V>
void Vector_t<V>::Insert(const V* _element)
{
	if (!_element)
	{
		return;
	}
	
	//TODO GrowIfNeeded
	
	m_vec[this->m_noe] = (V*)_element;
	++this->m_noe;
}

template <typename V>
void Vector_t<V>::Remove(const V& _element)
{
	int i = Index(_element);
	if (-1 == i)
	{
		return;
	}
	
	m_vec[i] = NULL;
	--this->m_noe;
	
	//TODO shift left
}

template <typename V>
void Vector_t<V>::RemoveAll()
{
	for (int i = 0; i < this->m_noe; ++i)
	{
		m_vec[i] = NULL;
	}
	
	this->m_noe = 0;
}

template <typename V>
void Vector_t<V>::RemoveAndDelete(const V& _element)
{
	int i = Index(_element);
	if (-1 == i)
	{
		return;
	}
	
	delete m_vec[i];	
	m_vec[i] = NULL;
	--this->m_noe;
	
	//TODO shift left
}

template <typename V>
void Vector_t<V>::RemoveAndDeleteAll()
{
	for (int i = 0; i < this->m_noe; ++i)
	{
		delete m_vec[i];
		m_vec[i] = NULL;
	}
	
	this->m_noe = 0;
}
	
#endif /* __VECTOR_T_H__ */








	

