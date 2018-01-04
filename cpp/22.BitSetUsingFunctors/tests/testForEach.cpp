#include <iostream>
#include <algorithm>
#include <numeric>      // std::accumulate


struct Accumulator {
    Accumulator() : sum(0) {}
    void operator() (int i) { sum += i;}
    int getCounter(void) const { return sum; }
    int sum;
};

template <typename T>
struct myclass {
    T operator()(T count, T _t) {
        for (; _t; _t >>= 1)
        {
            count += T(_t & 1);
        }
        
        return count;
    }
};


template <typename T>
void foo()
{
    T numbers[] = {1,2,128};
    unsigned count = std::accumulate(numbers, numbers+3, 0, myclass<T>());
    std::cout << count << std::endl;
}


int main ()
{
//    unsigned arr[] = {1, 2, 3, 8};
//    int init = 0;
    
//    Accumulator a;
//    std::for_each(arr, arr + 4, a);
//    std::cout << a.getCounter() << std::endl;
    foo<unsigned char>();
    
    return 0;
}







