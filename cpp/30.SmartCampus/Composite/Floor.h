#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "Composite.h"

namespace smartcampus
{


class Floor : Composite<ILocation>
{
public:
	// void AddChild(std::tr1::shared_ptr<T> _child);
	// void RemoveChild(std::tr1::shared_ptr<T> _child);
    
    virtual ~Floor();
    
    void Add(std::tr1::shared_ptr<ILocation> _location);
    void Remove(std::tr1::shared_ptr<ILocation> _location);
    std::tr1::shared_ptr<ILocation> 
        GetFloor(std::tr1::shared_ptr<ILocation> _location);

    const std::string& Floor() const;
    const std::string& Room() const;
    
private:        
    std::string m_floor;
    std::string m_room;
};


inline const std::string& Floor::Floor() const
{
    return m_floor;
}
inline const std::string& Room() const
{
    return m_room;
}

std::tr1::shared_ptr<ILocation>
        Floor::GetFloor(std::tr1::shared_ptr<ILocation> _location)
{
    it = find(m_locations.begin(), m_locations.end(), Floor(_location->Floor());
}

void Floor::Add(std::tr1::shared_ptr<ILocation> _location)
{
    if (_location->Floor() == "")
    {
        AddChild(_location);
    }
    
    std::tr1::shared_ptr<Composite<ILocation> >
                        floor = GetFloor(_location->Floor());
    if (!floor)
    {
        floor.reset(new Floor(_location->Floor()));
    }
}

  
  
    
    
}  // namespace smartcampus

#endif // __FLOOR_H__



