#include "Mutex.h"
#include "Guard.h"
#include "CondVar.h"
#include "Thread.h"
#include "mu_test.h"

#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
using namespace advcpp;

class Context{
public:
    Context();
    ~Context();
    sync::Mutex moo;
    sync::CondVar cv;
    pthread_t threads[10];
    unsigned counters[10];
    unsigned sums[10];
    unsigned threadCount;
};

Context::Context()
: cv(moo)
, threadCount(0)
{
    std::fill(counters, &counters[10], 0);
    std::fill(sums, &sums[10], 0);
    std::cout << "counters[" << "9" << "]: " << counters[9] << std::endl;
}

Context::~Context()
{
}

void Routine(void* _context)
{
    Context* context = (Context*)_context;
    sync::Guard guardianOfTheGalaxy(context->moo);

    unsigned threadIndex = context->threadCount++;
    // std::cout << "Routine: " << context->threadCount << std::endl;
    // std::cout << "Routine: " << context->counters[4] << std::endl;
    
    for (unsigned i = 0; i < 10; ++i)
    {
        ++context->counters[threadIndex];
        std::cout << "counters[" << threadIndex << "]: " << context->counters[threadIndex] << std::endl;
        usleep(20000);
    }

    // --context->threadCount;

    pthread_exit(0);
}


UNIT(Guard)
    sync::Mutex moo;
    sync::Guard guardianOfTheGalaxy(moo);
END_UNIT

UNIT(CondVar)
    Context context;

    // std::cout << "threadCount " << context.threadCount << std::endl;
    // std::cout << "counters " << context.counters[1] << std::endl;
    // std::cout << "sums: " << context.sums[2] << std::endl;


    for (unsigned i = 0; i < 10; ++i)
    {
        pthread_create(&context.threads[i], 0, (void* (*)(void*))Routine, (void*)&context.counters);
    }

    usleep(20000);

    for (unsigned i = 0; i < 10; ++i)
    {
        pthread_join(context.threads[i], 0);
    }

    ASSERT_THAT(10 == context.threadCount);
END_UNIT


class Test
{
public:
    Test() { std::cout << "Test::Test" << std::endl; }
    ~Test() { std::cout << "Test::~Test" << std::endl; }
    void TestRoutine() { std::cout << "Test::TestRoutine" << std::endl; }
};

UNIT(ThreadJoin)
    std::tr1::shared_ptr<Test> spObj(new Test);
    sync::Thread<Test> thread(spObj, &Test::TestRoutine);
    thread.Join();
    ASSERT_THAT(false == thread.IsJoinable());
END_UNIT

UNIT(ThreadDetach)
    std::tr1::shared_ptr<Test> spObj(new Test);
    sync::Thread<Test> thread(spObj, &Test::TestRoutine);
    // usleep(20000);
    thread.Detach();
    ASSERT_THAT(false == thread.IsJoinable());
END_UNIT

UNIT(ThreadJoinDetach)
    std::tr1::shared_ptr<Test> spObj(new Test);
    sync::Thread<Test> thread(spObj, &Test::TestRoutine);
    thread.Detach();
    thread.Join();
    ASSERT_THAT(false == thread.IsJoinable());
END_UNIT

//    std::cout << bs << std::endl;

TEST_SUITE(framework test)
    TEST(Guard)
    //TEST(CondVar)
    TEST(ThreadJoin)
    TEST(ThreadDetach)
//     TEST(ThreadJoinDetach)
END_SUITE



