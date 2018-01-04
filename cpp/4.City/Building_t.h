#ifndef __BUILDING_T_H__
#define __BUILDING_T_H__


template <class T>
class Building_t
{
public:
	Building_t(T _buildingID);
	Building_t(Building_t & _building);
	Building_t & operator=(Building_t & _building);
	
	void         SetBuildingID(T _buildingID);
	T            GetBuildingID();

private:
	T m_buildingID;
};


template <class T>
Building_t<T>::Building_t(T _buildingID)
{
	m_buildingID = _buildingID;
}

template <class T>
Building_t<T>::Building_t(Building_t & _building)
{
	m_buildingID = _building.m_buildingID;
}

template <class T>
Building_t<T> & Building_t<T>::operator=(Building_t & _building)
{
	m_buildingID = _building.m_buildingID;
	
	return *this;
}

template <class T>
void Building_t<T>::SetBuildingID(T _buildingID)
{
	m_buildingID  = _buildingID;
}

template <class T>
T Building_t<T>::GetBuildingID()
{
	return m_buildingID;
}




#endif /* __BUILDING_T_H__ */








