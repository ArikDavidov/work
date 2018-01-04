#ifndef TIME_AND_DATE_H
#define TIME_AND_DATE_H

#include <stdlib.h>

typedef struct{
	int hours;
	int minutes;
	int seconds;
}cTime_t;

typedeef cTime_t* timePtr_t;

typedef struct{
	int day;
	int month;
	int year;
}cDate_t;

typedef cDate_t* datePtr_t;

int SetTime(cTime_t* time, unsigned int hours, unsigned int minutes, unsigned int seconds);
int PtintTime(cTime_t* time, int format);
int GetHours(cTime_t* time);
int GetMinutes(cTime_t* time);
int GetSeconds(cTime_t* time);
int TimeAddition(cTime_t* time1, cTime_t* time2);

int SetDate(cDate_t* date, unsigned int day, unsigned int month, unsigned int year);
int PtintDate(cDate_t* date, int format);
int GetDay(cDate_t* date);
int GetMonth(cDate_t* date);
int GetYear(cDate_t* date);





#endif


