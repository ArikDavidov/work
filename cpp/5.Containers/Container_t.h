#ifndef __CONTAINER_T_H__
#define __CONTAINER_T_H__

/*
Default CTOR
Copy	CTOR
DTOR
Operator= 
*/

template <typename C>
class Container_t
{
public:
	Container_t();
	Container_t(const Container_t& _container);
	//virtual Container_t<C> & operator=(const Container_t& _container) = 0;
	virtual ~Container_t();

	virtual void Append(const C* _element, int _i) = 0;
	virtual void Prepend(const C* _element, int _i) = 0;
	virtual bool Contains(const C& _element) const = 0;
	virtual C*   Find(const C& _element) const = 0;
	virtual int  Index(const C& _element) const = 0;
	virtual void Insert(const C* _element) = 0;
	virtual void Remove(const C& _element) = 0;
	virtual void RemoveAll() = 0;
	virtual void RemoveAndDelete(const C& _element) = 0;
	virtual void RemoveAndDeleteAll() = 0;
	
	int  Count() const;
	bool IsEmpty() const;
	
protected:
	int m_noe;
	//Dlist: sentinels;
};

template <typename C>
Container_t<C>::Container_t()
{
	m_noe = 0;
}
template <typename C>
Container_t<C>::Container_t(const Container_t& _container)
{
	m_noe = _container.m_noe;
}

/*
template <typename C>
	Container_t<C> & operator=(const Container_t& _container);
{

}
*/
template <typename C>
int Container_t<C>::Count() const
{
	return m_noe;
}

template <typename C>
bool Container_t<C>::IsEmpty() const
{
	return 0 == m_noe;
}


#endif /* __CONTAINER_T_H__ */



