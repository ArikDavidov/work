#ifndef __LOCATION_H__
#define __LOCATION_H__

#include "Composite.h"

namespace smartcampus
{

class Location : Composite<ILocation>
{
public:
    virtual ~CompositeLocation();
    
    std::tr1::shared_ptr<ILocation> GetChiled(ILocation* _location);

    virtual const std::string& Floor() const;
    virtual const std::string& Room() const;
    
private:
    std::string m_floor;
    std::string m_room;
};


inline const std::string& Location::Floor() const
{
    return m_floor;
}
inline const std::string& Location::Room() const
{
    return m_room;
}

std::tr1::shared_ptr<ILocation> CompositeLocation::GetChiled(std::tr1::shared_ptr<ILocation> _location)
{
	find(m_locations.begin(), m_locations.end(), _location);
	
	return m_locations.find(_location);
}
    
    
    
    
}  // namespace smartcampus

#endif // __LOCATION_H__



