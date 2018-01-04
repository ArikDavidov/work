#include <iostream>
#include "Singleton.h"
using std::cout;
using std::endl;

const int NUM_OF_LOOPS = 10;
const int NUM_OF_THREADS = 100;

void* PrintFunc(void* _tid)
{
    cout << _tid << " got singleton: " << advcpp::Singleton<int>::GetInstance() << endl;

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_OF_THREADS];
    int i;
    int status;
    
    for (size_t j = 0; j < NUM_OF_LOOPS; ++j)
    {
        for (i = 0; i < NUM_OF_THREADS; ++i)
        {
            status = pthread_create(&threads[i], NULL, PrintFunc, (void*) &i);
            if (status != 0)
            {
                cout << "\nFailed to create thread " << i << endl;
            }
        }
        for (i = 0; i < NUM_OF_THREADS; ++i)
        {
            status = pthread_join(threads[i], NULL);
            if (status != 0)
            {
                cout << "\nFailed to join thread " << i << endl;
            }
        }
    }
    
    return 0;
}
