#include <string>
#include <sstream>  // ostringstream

namespace util
{


inline std::string Itoa(int _i)
{
    std::ostringstream ss;
    ss << _i;
    return ss.str();
}



}  // namespace util






