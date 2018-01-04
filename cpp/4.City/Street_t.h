#ifndef __STREET_T_H__
#define __STREET_T_H__


#include <vector>
using namespace std;


template <class T1, class T2>
class Street_t
{
public:
	Street_t(T1 _StreetID);
	Street_t(const Street_t& _street);
	Street_t<T1, T2> & operator=(const Street_t& _street);
	
	void SetStreetID(T1 _StreetID);
	T1   GetStreetID() const;
	void AddBuilding2Street(const Building_t<T2>* _building);
	T1   GetBuilding(Building_t<T2>* _building);

private:
	T1                       m_streetID;	
	vector<Building_t<T2> >  m_vec;
};

template <class T1, class T2>
Street_t<T1, T2>::Street_t(T1 _streetID)
{
	m_streetID = _streetID;
}

template <class T1, class T2>
Street_t<T1, T2>::Street_t(Street_t& _street)
{
	m_streetID = _street.m_streetID;
}

template <class T1, class T2>
Street_t<T1, T2> & Street_t<T1, T2>::operator=(Street_t& _street)
{
	m_streetID = _street.m_streetID;
	
	return *this;
}

template <class T1, class T2>
void Street_t<T1, T2>::SetStreetID(T1 _streetID)
{
	m_streetID  = _streetID;
}

template <class T1, class T2>
T1 Street_t<T1, T2>::GetStreetID()
{
	
	
	return m_streetID;
}

template <class T1, class T2>
void Street_t<T1, T2>::AddBuilding2Street(const Building_t<T2>* _building)
{
	m_vec.insert_back(_building);
}

template <class T1, class T2>
Building_t<T2>* GetBuilding()
{
	
}


#endif /* __STREET_T_H__ */

