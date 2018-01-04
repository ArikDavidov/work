#ifndef __TASK_H__
#define __TASK_H__

#include "STime.h"

#include <sys/types.h>

/** 
 * @brief Implement wraper functions for execution of repeating tasks.
 * 
 * @author Author Ariel Davidov (arik.davidov@gmail.com) 
*/


typedef struct Task Task;

typedef int (*TaskFunction) (void* _context); 


/**
 * @brief The function creates a task.
 * @param[in] _taskFunc user provided function to be executed
 * @param[in] _context context for _taskFunc
 * @param[in] _period_ms the frequency in milliseconds of _taskFunc execution
 * @param[in] _clockID clock identifier that specifies the clock against which
 * 					the execution interval is to be measured. Can be: CLOCK_REALTIME,
 *					CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID.
 * @return Task* on success / NULL on fail.
 *
 * @warning next execution time of the Task is not calculated on creation
 */
Task* TaskCreate(TaskFunction _taskFunc, void* _context, int _period_ms, const clockid_t _clockID);

/** 
 * @brief the function destroys a Task.
 * @param[in] _task pointer to Task to be destroyed
 * @return void
 */
void TaskDestroy(Task* _task);

/**
 * @brief Calculate the next execution time of the _task.
 * @param[in] _task user provided function to be executed
 * @param[in] _clockID clock identifier that specifies the clock against which
 * 					the execution interval is to be measured. Can be: CLOCK_REALTIME,
 *					CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID.
 * @return void
 */
void TaskCalculateNext(Task* _task, const clockid_t _clockID);

/**
 * @brief Execute _task. Wait for the execution time (if needed).
 * @param[in] _task user provided function to be executed
 * @param[in] _clockID clock identifier that specifies the clock against which
 * 					the execution interval is to be measured. Can be: CLOCK_REALTIME,
 *					CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID.
 * @return void
 */
int TaskExecute(Task* _task, const clockid_t _clockID);


/** 
 * @brief Function to compare Task execution time.
 * @return nonzero if _left earlier than _right, 0 otherwise
 */
int TaskLess(const Task* _left, const Task* _right);


#endif	/* #ifndef __TASK_H__ */
