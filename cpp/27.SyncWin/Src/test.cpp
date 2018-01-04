//#include "ThreadPool.h"
#include "Task.h"
#include "SafePriorityQueue.h"
#include "mu_test.h"
//#include "Mutex.h"
//#include "Guard.h"
//#include "CondVar.h"
//#include "Thread.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>        // std::runtime_error
#ifdef __linux__
#include <tr1/memory>		// std::tr1::shared_ptr
//#include <sys/syscall.h>	// syscall(SYS_gettid)
//#include <unistd.h>		// syscall(SYS_gettid)
#endif // !__linux__
#ifdef _WIN32
#include <memory>			// std::tr1::shared_ptr
#endif // _WIN32

using namespace advcpp;

// class TestClass
// {
// public:
//     explicit TestClass() {}
//     ~TestClass() {}
    
//     void DoSomeWork() {
//         std::cout << "TestClass::DoSomeWork: "
//                   << syscall(SYS_gettid) << std::endl;
//     }
// };


UNIT(PushPop)
    sync::SafePriorityQueue<std::tr1::shared_ptr<int> > q;
    q.Push(std::tr1::shared_ptr<int>(new int(30)));
    q.Push(std::tr1::shared_ptr<int>(new int(90)));
    q.Push(std::tr1::shared_ptr<int>(new int(25)));
    q.Push(std::tr1::shared_ptr<int>(new int(40)));
    ASSERT_THAT(90 == *q.Pop());
    ASSERT_THAT(40 == *q.Pop());
    ASSERT_THAT(30 == *q.Pop());
    ASSERT_THAT(25 == *q.Pop());
END_UNIT

//UNIT(ThreadPool)
//    sync::ThreadPool pool(1);
//    for (unsigned int i = 0; i < 1; i += 1)
//    {
//        pool.Add(std::tr1::shared_ptr<sync::Task>(new sync::Task));
//    }
//    pool.GracefulShutDown();
//END_UNIT  

//UNIT(BruteForceShutDown)
//    sync::ThreadPool pool(1);
//    pool.Add(std::tr1::shared_ptr<sync::Task>(new sync::Task));
//    pool.BruteForceShutDown();
//END_UNIT 

//    std::cout << bs << std::endl;

TEST_SUITE(framework test)
	TEST(PushPop)
	//TEST(ThreadPool)
	//TEST(BruteForceShutDown)
END_SUITE
    


