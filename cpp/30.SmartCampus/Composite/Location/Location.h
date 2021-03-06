#ifndef __LOCATION_H__
#define __LOCATION_H__

#include "Composite.h"

namespace smartcampus
{

class Location : Composite<ILocation>
{
public:
    explicit Location(const std::string& _floor = "", 
                      const std::string& _room = "");
    virtual ~Location();
    
    std::tr1::shared_ptr<ILocation> GetChiled(std::tr1::shared_ptr<ILocation> _location);
    
    virtual void GetRelevantFilters(const std::vector
                     <std::tr1::shared_ptr<ILocation> >& _res);
    virtual const std::string& Floor() const;
    virtual const std::string& Room() const;    
    
private:
    std::string m_floor;
    std::string m_room;
};



inline Location::Location(const std::string& _floor, 
                          const std::string& _room)
: m_floor(_floor)
, m_room(_room)
{    
}

inline Location::~Location()
{    
}

inline const std::string& Location::Floor() const
{
    return m_floor;
}
inline const std::string& Location::Room() const
{
    return m_room;
}

void Location::GetRelevantFilters
            (const std::vector<std::tr1::shared_ptr<ILocation> >& _res)
{
    for_each(m_children->begin(),m_children->end(), );
}

std::tr1::shared_ptr<ILocation> Location::GetChiled(std::tr1::shared_ptr<ILocation> _location)
{
	find(m_locations.begin(), m_locations.end(), _location);
	
	return m_locations.find(_location);
}
    
    
    
    
}  // namespace smartcampus

#endif // __LOCATION_H__



