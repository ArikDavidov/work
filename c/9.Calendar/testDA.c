#include<stdio.h>
#include"DailyAppointmentDiary.h"

int main(){

	int i=0, tempNum, tempReturned;
	unsigned int option, capacity, roomNum; 
	float startTime, endTime;
	Calendar_t* calendar=NULL;
	Meeting_t* tmpMeeting=NULL;
	int cont = 1;			// trigger to stop loop

	while (cont) {
		printf("                               \n");
		printf("Choose option:                 \n");
		printf("1: Create AD                   \n");
		printf("2: Create Meeting              \n");
		printf("3: Remove appointment from AD  \n");
		printf("4: Find appointment in AD      \n");
		printf("5: Destroy AD                  \n");
		printf("6: Print AD                    \n");
		printf("Any another number - stop      \n");

		scanf("%d", &option);
		switch (option) {
			case 1:
				printf("\nPlease enter the capacity:\n");
				scanf("%d", &capacity);
				calendar = CreateCalendar(capacity);
				if(calendar==NULL){
					printf("\nCreation faild!\n");
					return -1;
				}
				printf("\nAD was created\n");						break;
			case 2:
				printf("\nPlease enter start time:\n");
				scanf("%f", &startTime);
				printf("\nPlease enter end time:\n");
				scanf("%f", &endTime);
				printf("\nPlease enter room number:\n");
				scanf("%d", &roomNum);
				tmpMeeting = CreateMeeting(startTime, endTime, roomNum);
				if(tmpMeeting==NULL){
					printf("\nCreation faild!\n");					break;
				}
				tempReturned = InsertMeeting(calendar, tmpMeeting);
				if(tempReturned==-1){
					printf("\nInsertion faild!\n");
					free(tmpMeeting);								break;
				}
				printf("\nMeeting was inserted succesfuly!\n");		break;
			case 3:
				printf("\nPlease enter start time:\n");
				scanf("%f", &startTime);
				tempReturned = Remove(calendar, startTime);
				if(tempReturned==-1){
					printf("\nMeeting was not found\n");			break;
				}
				printf("\nMeeting was removed\n");					break;
			case 4:
				printf("\nPlease enter start time:\n");
				scanf("%f", &startTime);
				tmpMeeting = FindMeeting(calendar, startTime);
				if(tmpMeeting==NULL){
					printf("\nMeeting was not found.\n");			break;
				}
				printf("\nMeeting was found\n");					break;
			case 5:
				Destroy(calendar);
				calendar=NULL;
				printf("\nCalendar was destroyd!\n");				break;
			case 6:
				tempReturned = PrintCalendar(calendar);
				if(tempReturned==-1){
					printf("\nCalendar was not found.\n");
				}													break;
			default: cont = 0;										break;
		}
	}
	Destroy(calendar);
	return 0;
}

