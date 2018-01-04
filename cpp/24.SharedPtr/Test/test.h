#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>

template< bool b > 
struct algorithm_selector { 
  template< typename T > 
  static void implementation( T& object ) 
  { 
//implement the alorithm operating on "object" here 
  } 
};

template<> 
struct algorithm_selector< true > { 
  template< typename T > 
  static void implementation( T& object )   { 
    object.optimised_implementation(); 
  } 
};

template< typename T > 
void algorithm( T& object ) { 
  algorithm_selector< supports_optimised_implementation< T >::value >::implementation(object); 
}


class ObjectB { 
public: 
  void optimised_implementation() { 
//... 
  } 
};

template<> 
struct 
supports_optimised_implementation< ObjectB > { 
  static const bool value = true; 
};


//template< bool b > 
//struct algorithm_selector { 
//    template< typename T >
//    static void implementation( T& object ) 
//    { 
//        std::cout << "General" << std::endl;
//    } 
//};

//template<> 
//struct algorithm_selector< true > { 
//    template< typename T > 
//    static void implementation( T& object )
//    { 
//        std::cout << "Specialization" << std::endl; 
//    }
//};

//template< typename T > 
//void algorithm( T& object ) { 
//    algorithm_selector<supports_optimised_implementation<T>::value>::implementation(object); 
//}



#endif // __TEST_H__


