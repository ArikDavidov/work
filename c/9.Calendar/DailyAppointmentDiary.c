#include<stdlib.h>
#include<stdio.h>
#include"DailyAppointmentDiary.h"

Calendar_t* CreateCalendar(unsigned int capacity){
	Calendar_t* Calendar=NULL;
	Calendar_t* res=NULL;

	Calendar = malloc(sizeof(Calendar_t));
	if(Calendar!=NULL){
		Calendar->noe=0;
		Calendar->capacity = capacity;
		Calendar->meetingsArr = malloc(Calendar->capacity*sizeof(mtPtr));
		if(Calendar->meetingsArr!=NULL){
			res=Calendar;
		}
		else{
			free(Calendar);
		}
	}
	return res;
}

mtPtr CreateMeeting(float startTime, float endTime, unsigned int roomNum){
	mtPtr meeting=NULL;
	mtPtr res=NULL;
	
	if(startTime>=0.0 && endTime<=24.0 && endTime>startTime){
		meeting = malloc(sizeof(Meeting_t));
		if(meeting!=NULL){
			meeting->startTime = startTime;
			meeting->endTime = endTime;
			meeting->roomNum = roomNum;
			res = meeting;
		}
	}
	return res;
}

int OverlapCheck(Calendar_t* calendar, mtPtr meeting){
	int i=0, res=0;
	if(calendar->noe!=0){
		for(i=0; i<(calendar->noe); ++i){
			printf("%f %f", calendar->meetingsArr[i]->startTime, calendar->meetingsArr[i]->endTime);
			if(meeting->startTime < calendar->meetingsArr[i]->endTime){				
				if(meeting->endTime > calendar->meetingsArr[i]->endTime){
					res=-1;
					break;
				}
				if(meeting->endTime > calendar->meetingsArr[i]->startTime){
					res=-1;
					break;
				}
				res = i;
				break;
			}
		}
		res = calendar->noe + 1;
	}
	return res;	
}

int InsertMeeting(Calendar_t* calendar, mtPtr meeting){
	mtPtr* tempip;
	int i=0, res=-1;

	if(calendar!=NULL && meeting!=NULL){
		if(calendar->noe==calendar->capacity){
			tempip = realloc(calendar->meetingsArr, calendar->capacity*2*sizeof(mtPtr));
			if(tempip!=NULL){
				calendar->meetingsArr = tempip;
				calendar->capacity *=2;
			}
		}
		
		res = OverlapCheck(calendar, meeting);

		if(res!=-1){
			for(i=(calendar->noe); i>res; --i){
				calendar->meetingsArr[i] = calendar->meetingsArr[i-1];
			}
			calendar->meetingsArr[res] = meeting;
			++(calendar->noe);
		}	
	}
	return res;
}

int FindMeetingIndex(Calendar_t* calendar, float startTime){
	int i=0, res=-1;

	for(i=0; i<(calendar->noe); ++i){
		if((calendar->meetingsArr[i])->startTime == startTime){
			res = i;
			break;
		}
	}	
	return res;
}

mtPtr FindMeeting(Calendar_t* calendar, float startTime){
	int index=0;
	mtPtr res=NULL;

	if(startTime>=0.0 && startTime<24.0 && calendar!=NULL){
		index = FindMeetingIndex(calendar, startTime);
		if(index!=-1){
			res = calendar->meetingsArr[index];
		}
	}
	return res;
}

int Remove(Calendar_t* calendar, float startTime){
	int i=0, index, res=-1;

	if(startTime>=0.0 && startTime<24.0 && calendar!=NULL){
		index = FindMeetingIndex(calendar, startTime);
		if(index!=-1){
			free(calendar->meetingsArr[index]);
			for(i=index; i<(calendar->noe)-1; ++i){
				calendar->meetingsArr[i] = calendar->meetingsArr[i+1];		
			}
			--(calendar->noe);
			res=0;
		}
	}
	return res;
}

int PrintCalendar(Calendar_t* calendar){
	int i=0, res=-1;
	if(calendar!=NULL){
		if(calendar->noe==0){
			printf("\nNo meetings were found\n");
			res=0;
		}
		else{
			printf("\nMeetings:\n");
			for(i=0; i<(calendar->noe); ++i){
				printf("Start Time: %f  ",  (calendar->meetingsArr[i])->startTime);
				printf("End Time: %f  ",    (calendar->meetingsArr[i])->endTime);
				printf("Room Number: %d  ", (calendar->meetingsArr[i])->roomNum);
				printf("\n");
			}
			printf("\n");
			res=0;
		}
	}
	return res;
}

void Destroy(Calendar_t* calendar){
	if(calendar==NULL){
		return;
	}
	int i;
	for(i=0; i<(calendar->noe); ++i){
		free(calendar->meetingsArr[i]);
	}
	free(calendar->meetingsArr);
	free(calendar);
}

