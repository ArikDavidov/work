#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include "Task.h"

/*#include <stddef.h>*/			/* size_t */
#include <sys/types.h>

/** 
 * @brief Implement a facility that can execute periodic recurrent tasks
 * @details This facility behaves like a single threaded scheduler for running repeating tasks
 * The Periodic executor will execute tasks added to it. Each task can be executed more than one 
 * time. The period of the recurrence is set per task and each task can specify if it needs more 
 * execution cycles or it has finished
 *
 * @author Author Ariel Davidov (arik.davidov@gmail.com) 
*/

typedef struct PeriodicExecutor PeriodicExecutor;

PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clk_id);

void PeriodicExecutorDestroy(PeriodicExecutor* _scheduler);

int PeriodicExecutorAdd(PeriodicExecutor* _scheduler, TaskFunction _taskFunc, void* _context, int _period_ms);


/**  
 * @brief Apply a heap policy over a Vector container.  
 * @param[in] _scheduler - Vector that hold the elements, must be initialized
 * @param[in] _pfLess - A less than comparator to be used to compare elements 
 * @return Heap * - on success
 * @retval 0 on fail or if the scheduler is already running. 
 *
 * @warning Compile with -std=gnu99 flag.
 */
size_t PeriodicExecutorRun(PeriodicExecutor* _scheduler);

size_t PeriodicExecutorPause(PeriodicExecutor* _scheduler);


#endif	/* #ifndef __SCHEDULER_H__ */








