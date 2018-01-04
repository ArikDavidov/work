#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TimeAndDate.h"
#define  DAYS_IN_MONTHS {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}


int SetTime(timePtr_t* timePtrPtr, unsigned int hours, unsigned int minutes, unsigned int seconds){
	int res;
	
	if(*timePtrPtr != NULL && hours < 24 && minutes < 60 && seconds < 60){
		timePtr->hours   = hours;
		timePtr->minutes = minutes;
		timePtr->seconds = seconds;
		res = 0;
	}
	else{
		*timePtrPtr = NULL;
		res = -1;
	}
	return res;
}

int PtintTime(cTime_t* timePtr, int format){
	int res = -1;
	if(timePtr != NULL){
		if(format == 1){
			printf("%d:%02d:%02d\n", timePtr->hours, timePtr->minutes, timePtr->seconds);
			res = 0;
		}
		else if(format == 0){
			if(timePtr->hours > 12){
				printf("%d:%02d:%02d PM\n", (timePtr->hours - 12), timePtr->minutes, timePtr->seconds);
			}
			else{
				printf("%d:%02d:%02d AM\n", timePtr->hours, timePtr->minutes, timePtr->seconds);
			}
			res = 0;
		}
	}
	return res;
}

int GetHours(cTime_t* timePtr){
	int res = -1;
	if(timePtr != NULL){
		res = timePtr->hours;
	}
	return res;
}
int GetMinutes(cTime_t* timePtr){
	int res = -1;
	if(timePtr != NULL){
		res = timePtr->minutes;
	}
	return res;
}
int GetSeconds(cTime_t* timePtr){
	int res = -1;
	if(timePtr != NULL){
		res = timePtr->seconds;
	}
	return res;
}

int TimeAddition(cTime_t* time1, cTime_t* time2){
	int res = -1, totalSeconds = 0;

	if(time1 != NULL && time2 != NULL){	
		totalSeconds += ((time1->hours * 60) + time1->minutes) * 60 + time1->seconds;
		totalSeconds += ((time2->hours * 60) + time2->minutes) * 60 + time1->seconds;
		
		time1->seconds = totalSeconds % 60;
		totalSeconds /= 60;
		time1->minutes = totalSeconds % 60;
		totalSeconds /= 60;
		time1->hours = totalSeconds % 24;
		res = 0;
	}
	return res;
}

int SetDate(datePtr_t* datePtrPtr, unsigned int day, unsigned int month, unsigned int year){
	int res;
	
	if(*datePtrPtr != NULL && year < 3000 && month < 13 && day < 32){
		datePtrPtr->day   = day;
		datePtrPtr->month = month;
		datePtrPtr->year = year;
		res = 0;
	}
	else{
		*datePtrPtr = NULL;
		res = -1;
	}
	return res;	
}

int PtintDate(cDate_t* date, int format){

}

int GetDay(cDate_t* date){
	int res = -1;
	if(timePtr != NULL){
		res = date->day;
	}
	return res;
}

int GetMonth(cDate_t* date){
	int res = -1;
	if(timePtr != NULL){
		res = date->month;
	}
	return res;
}

int GetYear(cDate_t* date){
	int res = -1;
	if(timePtr != NULL){
		res = date->year;
	}
	return res;
}

int GetDayOfYear(cDate_t* date){
	int res = -1;
	int daysInMonths[] = DAYS_IN_MONTHS;
	
	if(timePtr != NULL){
		for(i = 0; i < date->month; ++i){
			da
		}
		res = date->year;
	}
	return res;
}

int IsLeapYear(cDate_t* date){
	int res = -1;
	if(timePtr != NULL){
		if(date->year % 4) {res = 1;}
		else {res = 0;}
		}
	return res;
}
