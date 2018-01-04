#include <vector>
#include <list>

#include <iostream>
#include <algorithm>


void Print(int i) {  // function:
  std::cout << i << std::endl;
}



struct Accumulator {
    Accumulator() : sum(0) {}
    int operator() (int i) {sum += i; return i;}
    int sum;
    void Print() { std::cout << sum << std::endl; }
} ;

//int ClassPrint::m_sum = 0;

int main ()
{
    std::vector<int> vec;
    std::list<int>   list;
    
  
    for (unsigned int i = 0; i < 4; ++i)
    {
        list.push_back(i);
    }    
    
    Accumulator result = for_each(list.begin(), list.end(), Accumulator()); // Accumulator() creates tmp obj
    
    result.Print();
    
    return 0;
}




