#ifndef __S_TIME_H__
#define __S_TIME_H__

#include "STime.h"

#include <time.h>		/* struct timespec, clock_gettime (link with -lrt flag), */
#include <stdlib.h>

/* #define NDEBUG 1 */
#include <assert.h>

#define NANOSECONDS_IN_SECOND	1000000000
#define OVERFLOW_OCCURRED(N)	((N) >= NANOSECONDS_IN_SECOND)
#define MILLI_2_NANO(M)			((M) * 1000000)
#define MILLI_2_SECONDS(M)		((M) / 1000)


struct Time
{
	struct timespec	m_ts;
};


Time* TimeCreate(int _milliseconds)
{
	Time* time;
	
	time = malloc(sizeof(Time));
	if (!time)
	{
		return NULL;
	}
	
	time->m_ts.tv_nsec = MILLI_2_NANO(_milliseconds) % NANOSECONDS_IN_SECOND;
	time->m_ts.tv_sec  = MILLI_2_SECONDS(_milliseconds);
	
	return time;
}

Time* TimeCreateCurrent(const clockid_t _clockID)
{
	int ret;
	
	Time* time;
	
	time = malloc(sizeof(Time));
	if (!time)
	{
		return NULL;
	}
	
	ret = clock_gettime(_clockID, &(time->m_ts));
	assert(!ret);	
	
	return time;
}

void TimeGetCurrent(const clockid_t _clockID, Time* _time)
{
	int ret;
	
	assert(time);
	if (!_time)
	{
		return;
	}
	
	ret = clock_gettime(_clockID, &(_time->m_ts));
	assert(!ret);
}

void TimeDestroy(Time* _time)
{
	if (!_time)
	{
		return;
	}

	free(_time);
}

int TimeLess(const Time* _left, const Time* _right)
{
	if (!_left || !_right)
	{
		return 0;
	}
	
	return (_left->m_ts.tv_sec == _right->m_ts.tv_sec) ?
			(_left->m_ts.tv_nsec < _right->m_ts.tv_nsec) :
			(_left->m_ts.tv_sec < _right->m_ts.tv_sec);	
}


void TimeSleepUntil(const clockid_t _clockID, const Time* _wakeUpTime)
{
	int ret;
	Time current;


	if (!_wakeUpTime)
	{
		return;
	}

	ret = clock_gettime(_clockID, &(current.m_ts));
	assert(!ret);

	if(TimeLess(_wakeUpTime, &current))
	{
		return;
	}

	ret = clock_nanosleep(_clockID, TIMER_ABSTIME, &_wakeUpTime->m_ts, NULL);
	assert(!ret);
}

void TimeAdd(Time* _result, const Time* _added)
{
	long nanoseconds;
	
	if (!_result || !_added)
	{
		return;
	}
	
	nanoseconds = _result->m_ts.tv_nsec + _added->m_ts.tv_nsec;
	
	_result->m_ts.tv_nsec = nanoseconds % NANOSECONDS_IN_SECOND;
	_result->m_ts.tv_sec += _added->m_ts.tv_sec + (OVERFLOW_OCCURRED(nanoseconds)) ? 1 : 0;

}

#endif	/* #ifndef __S_TIME_H__ */
