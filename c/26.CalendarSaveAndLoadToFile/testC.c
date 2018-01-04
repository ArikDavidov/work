#include <stdio.h>
#include "Calendar.h"

#define DEFAULT_CAPACITY 2
#define FILE_NAME "Calendar.txt"

int Load();
int Save(Calendar_t* _calendar);

int main(){

	int ret;
	unsigned int option, capacity, roomNum; 
	float startTime, endTime;
	Calendar_t* calendar = NULL;
	Meeting_t* tmpMeeting = NULL;
	int cont = 1;			/* trigger to stop loop */

	while (cont) 
	{
		printf("                               \n");
		printf("Choose option:                 \n");
		printf("1: Create AD                   \n");
		printf("2: Load AD                     \n");
		printf("3: Create Meeting              \n");
		printf("4: Remove appointment from AD  \n");
		printf("5: Find appointment in AD      \n");
		printf("6: Destroy AD                  \n");
		printf("7: Print AD                    \n");
		printf("Any another number - stop      \n");

		scanf("%u", &option);
		switch (option) 
		{
			case 1:
				calendar = CreateCalendar(DEFAULT_CAPACITY);
				if(NULL == calendar)
				{
					printf("\nCreation faild!\n");
					return -1;
				}
				printf("\nAD was created\n");						break;
			case 2:
				ret = Load(calendar, FILE_NAME);
				if(0 == ret)
				{
					printf("\nLoading faild.\n");
					return -1;
				}
				printf("\nLoading was succesful.\n");				break;
			case 3:
				printf("\nPlease enter start time:\n");
				scanf("%f", &startTime);
				printf("\nPlease enter end time:\n");
				scanf("%f", &endTime);
				printf("\nPlease enter room number:\n");
				scanf("%u", &roomNum);
				tmpMeeting = CreateMeeting(startTime, endTime, roomNum);
				if(NULL == tmpMeeting)
				{
					printf("\nCreation faild!\n");					break;
				}
				ret = InsertMeeting(calendar, tmpMeeting);
				if(-1 == ret)
				{
					printf("\nInsertion faild!\n");
					free(tmpMeeting);								break;
				}
				printf("\nMeeting was inserted succesfuly!\n");		break;
			case 4:
				printf("\nPlease enter start time:\n");
				scanf("%f", &startTime);
				ret = Remove(calendar, startTime);
				if(-1 == ret)
				{
					printf("\nMeeting was not found\n");			break;
				}
				printf("\nMeeting was removed\n");					break;
			case 5:
				printf("\nPlease enter start time:\n");
				scanf("%f", &startTime);
				tmpMeeting = FindMeeting(calendar, startTime);
				if(tmpMeeting==NULL)
				{
					printf("\nMeeting was not found.\n");			break;
				}
				printf("\nMeeting was found\n");					break;
			case 6:
				Destroy(calendar);
				calendar = NULL;
				printf("\nCalendar was destroyd!\n");				break;
			case 7:
				ret = PrintCalendar(calendar);
				if(-1 == ret)
				{
					printf("\nCalendar was not found.\n");
				}													break;
			default: cont = 0;										break;
		}
	}
	ret = Save(calendar);
	if (0 == ret)
	{
		printf("\nCalendar was saved.\n");
	}
	else
	{
		printf("\nCalendar wasn't saved.\n");
	}
	Destroy(calendar);
	return 0;
}

