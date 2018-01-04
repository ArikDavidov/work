#ifndef __LOCATION_H__
#define __LOCATION_H__

#include <string>
#include <vector>
#include <algorithm>
#include <tr1/memory>


namespace smartcampus
{


class ILocation
{
public:
    virtual ~ILocation();
    
    virtual void GetRelevantFilters(const std::vector
                     <std::tr1::shared_ptr<ILocation> >& _res) = 0;
    virtual std::string Floor() const = 0;
    virtual std::string Room() const = 0;
};

    

    
}  // namespace smartcampus

#endif // __LOCATION_H__


