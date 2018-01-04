#ifndef DAILY_APPOINTMENT_DIARY_H
#define DAILY_APPOINTMENT_DIARY_H

#include<stdlib.h>

typedef struct{
	float startTime;
	float endTime;
	int roomNum;
}Meeting_t;

typedef Meeting_t* mtPtr;

typedef struct{
	mtPtr* meetingsArr;
	int capacity;
	int noe;
}Calendar_t;

Calendar_t* CreateCalendar (unsigned int capacity);
mtPtr   	CreateMeeting  (float startTime, float endTime, unsigned int roomNum);
int     	InsertMeeting  (Calendar_t* calendar, mtPtr meeting);
mtPtr     	FindMeeting    (Calendar_t* calendar, float StartTime);
int     	Remove         (Calendar_t* calendar, float StartTime);
int			PrintCalendar  (Calendar_t* calendar);
void    	Destroy        (Calendar_t* calendar);

#endif
