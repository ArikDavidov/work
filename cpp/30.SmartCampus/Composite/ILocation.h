#ifndef __LOCATION_H__
#define __LOCATION_H__

#include <string>
#include <vector>
#include <algorithm>

namespace smartcampus
{


class ILocation
{
public:
    virtual ~ILocation();
    
    virtual std::string Floor() const = 0;
    virtual std::string Room() const = 0;
};

    

    
    
}  // namespace smartcampus

#endif // __LOCATION_H__


