#include "Scheduler.h"
#include "Task.h"
#include "STime.h"

#include "mu_test.h"

#include <time.h>	/* clockid_t */
#include <stdio.h>
#include <unistd.h>	/* usleep */


typedef struct 
{
	struct timespec	m_ts;
} TestTime;

typedef struct 
{
	TaskFunction	m_taskFunc;
	void*			m_context;
	Time*			m_nextTime;
	Time*			m_interval;
} TestTask;

void TimePrint(TestTime* _time)
{
	printf("%ld.%09ld\n", _time->m_ts.tv_sec, _time->m_ts.tv_nsec);
}

int TestIncrement(int* _x)
{
	++(*_x);

	return (10 > *_x) ? 0 : 1;
}

/************************* Time **************************/

UNIT(TestTimeAddOverflow)
	TestTime* a = NULL;
	TestTime* b = NULL;
	TestTime* expected = NULL;

	a = (TestTime*)TimeCreate(900);
	b = (TestTime*)TimeCreate(900);
	TimeAdd((Time*)a, (Time*)b);
	expected = (TestTime*)TimeCreate(1800);

	ASSERT_THAT(a->m_ts.tv_sec == expected->m_ts.tv_sec);
	ASSERT_THAT(a->m_ts.tv_nsec == expected->m_ts.tv_nsec);
END_UNIT

UNIT(TestTimeLess)
	TestTime* a = NULL;
	TestTime* b = NULL;

	a = (TestTime*)TimeCreate(1);
	b = (TestTime*)TimeCreate(0);
	ASSERT_THAT(0 == TimeLess((Time*)a, (Time*)b));
	ASSERT_THAT(1 == TimeLess((Time*)b, (Time*)a));
END_UNIT

UNIT(TestTimeSleepUntil)
	TestTime* a = NULL;
	TestTime* b = NULL;
	TestTime* interval = NULL;

	a = (TestTime*)TimeCreateCurrent(CLOCK_REALTIME);
	interval = (TestTime*)TimeCreate(200);
	TimeAdd((Time*)a, (Time*)interval);
	TimeSleepUntil(CLOCK_REALTIME, (Time*)a);

	/* Checki _taskng that slept not less than needed */
	b = (TestTime*)TimeCreateCurrent(CLOCK_REALTIME);
	ASSERT_THAT(TimeLess((Time*)a, (Time*)b));
	
	/* Checking that slept not more then needed (2 ms delay allowed) */
	TimeAdd((Time*)a, TimeCreate(2));
	ASSERT_THAT(TimeLess((Time*)b, (Time*)a));
END_UNIT

UNIT(TestTimeGetCurrent)
	TestTime* a = NULL;
	TestTime* b = NULL;

	a = (TestTime*)TimeCreateCurrent(CLOCK_REALTIME);
	b = (TestTime*)TimeCreate(0);
	TimeGetCurrent(CLOCK_REALTIME, (Time*)b);
	/* Checking that b is within expected boundaries (1 ms) */
	ASSERT_THAT(TimeLess((Time*)a, (Time*)b));
	TimeAdd((Time*)a, TimeCreate(1));
	ASSERT_THAT(TimeLess((Time*)b, (Time*)a));
END_UNIT


/************************* Task **************************/

UNIT(TestTaskCalculateNext)
	Time* a = NULL;
	Time* b = NULL;
	Task* task = NULL;

	a = TimeCreateCurrent(CLOCK_REALTIME);
	task = TaskCreate(NULL, NULL, 300, CLOCK_REALTIME);
	TaskCalculateNext(task, CLOCK_REALTIME);
	TimeAdd(a, TimeCreate(300));
	b = ((TestTask*)task)->m_nextTime;
	/* Checking that b is within expected boundaries (1 ms) */
	ASSERT_THAT(TimeLess(a, b));
	TimeAdd(a, TimeCreate(1));
	ASSERT_THAT(TimeLess(b, a));
END_UNIT

UNIT(TestTaskExecute)
	Task* task = NULL;
	int x = 5;
	
	task = TaskCreate((TaskFunction)TestIncrement, &x, 100, CLOCK_REALTIME);
	do
	{
		TaskCalculateNext(task, CLOCK_REALTIME);
	} while (0 == TaskExecute(task, CLOCK_REALTIME));

	ASSERT_THAT(10 == x);
END_UNIT

UNIT(TestTaskLess)
	Task* a = NULL;
	Task* b = NULL;
	
	a = TaskCreate(NULL, NULL, 100, CLOCK_REALTIME);
	TaskCalculateNext(a, CLOCK_REALTIME);
	b = TaskCreate(NULL, NULL, 100, CLOCK_REALTIME);
	TaskCalculateNext(b, CLOCK_REALTIME);
	ASSERT_THAT(1 == TaskLess(a, b));
	TaskCalculateNext(a, CLOCK_REALTIME);
	ASSERT_THAT(1 == TaskLess(b, a));
END_UNIT

/************************* Scheduler **************************/

UNIT(TestScheduler)
	PeriodicExecutor* scheduler = NULL;
	int x = 5;

	scheduler = PeriodicExecutorCreate("Test1", CLOCK_REALTIME);
	ASSERT_THAT(0 == PeriodicExecutorAdd(scheduler, 
						(TaskFunction)TestIncrement, &x, 100));
END_UNIT

UNIT(TestScheduler)
	PeriodicExecutor* scheduler = NULL;
	int x = 5;

	scheduler = PeriodicExecutorCreate("Test1", CLOCK_REALTIME);
	ASSERT_THAT(0 == PeriodicExecutorAdd(scheduler, 
						(TaskFunction)TestIncrement, &x, 100));
END_UNIT


TEST_SUITE(framework test)
	TEST(TestTimeAddOverflow)
	TEST(TestTimeLess)
	TEST(TestTimeSleepUntil)
	TEST(TestTimeGetCurrent)

	TEST(TestTaskCalculateNext)
	TEST(TestTaskExecute)
	TEST(TestTaskLess)

	TEST(TestScheduler)
	/* TODO Check that no starvation occures. 3 tasks same time and intervals 123123123 and not 111222333*/
	/* TODO Pause and rerun */
END_SUITE





