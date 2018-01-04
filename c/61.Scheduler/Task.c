#include "Task.h"

#include <stdlib.h>
#include <stdio.h>

struct Task
{
	TaskFunction	m_taskFunc;
	void*			m_context;
	Time*			m_nextTime;
	Time*			m_interval;
};


Task* TaskCreate(TaskFunction _taskFunc, void* _context, int _period_ms, const clockid_t _clockID)
{
	Task* task = NULL;
	
	task = malloc(sizeof(Task));
	if (!task)
	{
		return NULL;
	}
	
	task->m_interval = TimeCreate(_period_ms);
	if (!task->m_interval)
	{
		free(task);
		return NULL;
	}
	task->m_nextTime = TimeCreate(0);
	if (!task->m_nextTime)
	{
		TimeDestroy(task->m_interval);
		free(task);
		return NULL;
	}

	task->m_taskFunc = _taskFunc;
	task->m_context  = _context;
	
	return task;
}

void TaskDestroy(Task* _task)
{

}

void TaskCalculateNext(Task* _task, const clockid_t _clockID)
{
	if (!_task)
	{
		return;
	}
	
	TimeGetCurrent(_clockID, _task->m_nextTime);
	TimeAdd(_task->m_nextTime, _task->m_interval);
}

int TaskExecute(Task* _task, const clockid_t _clockID)
{
	int ret;

	if (!_task)
	{
		return 1;
	}

	TimeSleepUntil(_clockID, _task->m_nextTime);
	ret = _task->m_taskFunc(_task->m_context);


	return ret;
}

int TaskLess(const Task* _left, const Task* _right)
{
	return TimeLess(_left->m_nextTime, _right->m_nextTime);
}





