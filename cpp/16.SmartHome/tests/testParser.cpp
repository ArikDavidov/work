// ws manipulator example
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream, std::ws

int main () {

    std::string line("   one   =  \t two    ");
    
    if (line.find('=') != line.rfind('='))
    {
        std::cout << "not according to \"key = value\" format"
                  << std::endl;
    }

    std::string key, value;
    std::istringstream iss (line);
    
    Trim(getline(iss, key, '='));
    Trim(getline(iss, value));

    if (key == "" || value == "")
    {
        std::cout << "not according to \"key = value\' format"
                  << std::endl;
    }

    return 0;
}

//  char a[10], b[10];
//    iss >> std::ws >> a >> std::ws >> b >> std::ws >> c;
//    std::cout << a << "|" << b << "|" << c << "|" << std::endl;
    
//  std::string str ("The sixth sick ='s sixth sheep's sick.");
//  std::string key ("sixth");

//  std::size_t found = str.rfind(=);
//  if (found!=std::string::npos)
//    str.replace (found,key.length(),"seventh");

