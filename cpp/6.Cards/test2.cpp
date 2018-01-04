// string::data
#include <iostream>
#include <string>
#include <cstring>

int main ()
{
  int length;

  std::string str[] = {"Test string", "Test string2"};
  char* cstr = "Test string";

  if ( str[0].length() == std::strlen(cstr) )
  {
    std::cout << "str and cstr have the same length.\n";

    if ( memcmp (cstr, str[0].data(), str[1].length() ) == 0 )
      std::cout << "str and cstr have the same content.\n";
  }
  return 0;
}


