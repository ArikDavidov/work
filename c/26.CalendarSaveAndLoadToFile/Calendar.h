#ifndef __DAILY_APPOINTMENT_DIARY_H__
#define __DAILY_APPOINTMENT_DIARY_H__

#include<stdlib.h>

typedef struct Meeting_t Meeting_t;
typedef Meeting_t* mtPtr;
typedef struct Calendar_t Calendar_t;

Calendar_t* CreateCalendar (unsigned int capacity);
mtPtr   	CreateMeeting  (float startTime, float endTime, unsigned int roomNum);
int     	InsertMeeting  (Calendar_t* calendar, mtPtr meeting);
mtPtr     	FindMeeting    (Calendar_t* calendar, float StartTime);
int     	Remove         (Calendar_t* calendar, float StartTime);
int			PrintCalendar  (Calendar_t* calendar);
void    	Destroy        (Calendar_t* calendar);

#endif /* __DAILY_APPOINTMENT_DIARY_H__ */

