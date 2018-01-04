#include "Scheduler.h"
#include "Task.h"
#include "STime.h"
#include "Heap.h"
#include "Vector.h"

#include <stdlib.h>
#include <string.h>		/* strcpy */


typedef Heap PriorityQueue;

struct PeriodicExecutor
{
	PriorityQueue*	m_priorityQ;
	size_t			m_runCycles;
	int				m_pauseRequest;
	char			m_name[128];
	clockid_t		m_clockID;
	/* TODO m_magic */
};


PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clk_id)
{
	PeriodicExecutor* scheduler = NULL;
	Vector* vec = NULL;
	
	scheduler = malloc(sizeof(PeriodicExecutor));
	if (!scheduler)
	{
		return NULL;
	}

	vec = VectorCreate(32, 16);

	scheduler->m_priorityQ = HeapBuild(vec, (int (*)(const void *, const void *))TaskLess);
	if (!scheduler->m_priorityQ)
	{
		VectorDestroy(&vec, (void (*)(void *))TaskDestroy);
		free(scheduler);
		return NULL;
	}
	
	scheduler->m_clockID      = _clk_id;
	scheduler->m_runCycles    = 0;
	scheduler->m_pauseRequest = 0;
	
	strcpy(scheduler->m_name, _name);

	return scheduler;
}
/*
void PeriodicExecutorDestroy(PeriodicExecutor* _scheduler)
{
	Vector* vec = NULL;
	
	vec = HeapDestroy(&scheduler->m_priorityQ);
	TODO void (*_elementDestroy)(void* _item))
	VectorDestroty(&vec, );
	
	free(scheduler);
}
*/

int PeriodicExecutorAdd(PeriodicExecutor* _scheduler, TaskFunction _taskFunc, void* _context, int _period_ms)
{
	Task* task = NULL;
	int ret;
	
	task = TaskCreate(_taskFunc, _context, _period_ms, _scheduler->m_clockID);
	if (!task)
	{
		return 1;
	}
	ret = HeapInsert(_scheduler->m_priorityQ, (void*)task);

	return (!ret) ? 0 : 1;
}

size_t PeriodicExecutorRun(PeriodicExecutor* _scheduler)
{
	Task* task = NULL;

	if (!_scheduler)
	{
		return 0;
	}
	
	_scheduler->m_pauseRequest = 0;
	
	while (!_scheduler->m_pauseRequest && 0 < HeapSize(_scheduler->m_priorityQ))
	{
		task = HeapExtract(_scheduler->m_priorityQ);
		
		if (0 == TaskExecute(task, _scheduler->m_clockID))
		{
			TaskCalculateNext(task, _scheduler->m_clockID);
			HeapInsert(_scheduler->m_priorityQ, task);
		}
		else
		{
			TaskDestroy(task);
		}
		
		++_scheduler->m_runCycles;
	}
	
	return _scheduler->m_runCycles;
}

size_t PeriodicExecutorPause(PeriodicExecutor* _scheduler)
{
	if (!_scheduler)
	{
		return 0;
	}
	
	_scheduler->m_pauseRequest = 1;
	
	return HeapSize(_scheduler->m_priorityQ);
}











