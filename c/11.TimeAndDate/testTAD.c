#include<stdio.h>
#include"TimeAndDate.h"

int main(){
	cTime_t time;
	timePtr_t timePtr;
	cDate_t date; 
	datePtr_t datePtr;
	int res;
	unsigned int hours, minutes, seconds;

    timePtr = &time;
	printf("Enter hours:\n");
	scanf("%d", &hours);
	printf("Enter minutes:\n");
	scanf("%d", &minutes);	
	printf("Enter seconds:\n");
	scanf("%d", &seconds);

	SetTime(&timePtr, hours, minutes, seconds);

	if(timePtr != NULL){

		PtintTime(timePtr, 0);
		PtintTime(timePtr, 1);

		printf("GetHours:   %d\n", GetHours(timePtr));
		printf("GetMinutes: %d\n", GetMinutes(timePtr));
		printf("GetSeconds: %d\n", GetSeconds(timePtr));
		TimeAddition(timePtr, timePtr);
		PtintTime(timePtr, 1);
	}
	else{
		printf("Invalid time!\n");
	}

	SetDate(date, day, month, year);
	
	if(datePtr != NULL){
		printf("GetDay:   %d\n", GetDay(date));
		printf("GetMonth: %d\n", GetMonth(date));
		printf("GetYear:  %d\n", GetYear(date));
	}
	return 0;
}

