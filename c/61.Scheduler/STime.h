#ifndef __S_TIME_h__
#define __S_TIME_h__

#include <sys/types.h>

/** 
 * @brief Utility module providing time related functionality
 *
 * @author Author Ariel Davidov (arik.davidov@gmail.com) 
*/

typedef struct Time Time;


/** 
 * @brief Create Time and set it to the user provided value in milliseconds
 * @param[im] _milliSecs value in milliseconds
 * @return pointer to the created Time
 */
Time* TimeCreate(int _milliSecs);

/** 
 * @brief Create Time and set it to the current time of the clock specified by _clockID
 * @param[in] _clockID clock identifier. Can be:
 *				CLOCK_REALTIME System-wide realtime clock. 
 *				CLOCK_MONOTONIC Clock that cannot be set and represents monotonic time since
 * 								some unspecified starting point. 
 *				CLOCK_PROCESS_CPUTIME_ID High-resolution per-process timer from the CPU.
 *				CLOCK_THREAD_CPUTIME_ID Thread-specific CPU-time clock. 
 * @return pointer to the created Time
 */
Time* TimeCreateCurrent(const clockid_t _clockID);

/** 
 * @brief Set the user provided _time to the current time of the clock specified by _clockID
 * @param[in] _clockID clock identifier. Can be: CLOCK_REALTIME, CLOCK_MONOTONIC,
 *						CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID.
 * @param[in] _time pointer to time to be set
 * @return void
 */
void TimeGetCurrent(const clockid_t _clockID, Time* _time);

/** 
 * @brief the function destroys a Time.
 * @param[in] _time pointer to Time to be destroyed
 * @return void
 */
void TimeDestroy(Time* _time);

/** 
 * @brief Function to compare Times.
 * @return 1 if _left smaller than _right, nonzero otherwise
 */
int TimeLess(const Time* _left, const Time* _right);

/** 
 * @brief Suspend the calling prosses until the _wakeUpTime specified by _clockID.
 * @param[in] _clockID clock identifier that specifies the clock against which
 * 					the sleep interval is to be measured. Can be: CLOCK_REALTIME,
 *					CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID.
 * @param[in] _wakeUpTime pointer to wake up time specified as an absolute value of the _clockID.
 * @return void
 */
void TimeSleepUntil(const clockid_t _clockID, const Time* _wakeUpTime);

/** 
 * @brief Add two Times 
 * @param[in/out] pointer to Time to be added and to recive the result.
 * @param[in] pointer to Time to be added.
 * @return void
 */
void TimeAdd(Time* _result, const Time* _added);


#endif /* #ifndef __S_TIME_h__ */


