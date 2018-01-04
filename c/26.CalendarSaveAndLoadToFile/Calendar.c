#include <stdlib.h>
#include <stdio.h>
#include "Calendar.h"

#define FILE_NAME "Calendar.txt"
#define MAX_STRING_LENGTH 128

struct Meeting_t
{
	float startTime;
	float endTime;
	int roomNum;
};

struct Calendar_t
{
	mtPtr* m_arr;
	int capacity;
	int noe;
};

int Load(Calendar_t* _calendar, char* _fileName)
{
	int res = -1;
	char str[MAX_STRING_LENGTH];
	float startTime, endTime;
	unsigned int roomNum;
	Meeting_t* meeting = NULL;
	FILE* fp = NULL;
	
	if(NULL == _calendar)
	{
		return res;
	}
	if(NULL != (fp = fopen(_fileName, "r")))
	{		
		res = 0;
		while(1)
		{	
			fscanf(fp, "%f%f%u", &startTime, &endTime, &roomNum);
			if (feof(fp))
			{
				break;
			}
			meeting = CreateMeeting(startTime, endTime, roomNum);
			if(NULL == meeting)
			{
				res = -1;
				break;
			}
			res = InsertMeeting(_calendar, meeting);
			if(0 != res)
			{
				free(meeting);
				res = -1;
				break;
			}
		}		
		res = fclose(fp);
	}	
	return res;
}

int Save(Calendar_t* _calendar)
{
	int i = 0, res = -1;
	FILE* fp = NULL;
	
	if(NULL == _calendar || 0 == _calendar->noe)
	{
		return res;
	}
	if(NULL != (fp = fopen(FILE_PATH, "w")))
	{
		for(i = 0; i < _calendar->noe; ++i)
		{
			fprintf(fp, "%f", _calendar->m_arr[i]->startTime);
			fprintf(fp, "%f", _calendar->m_arr[i]->endTime);
			fprintf(fp, "%d", _calendar->m_arr[i]->roomNum);
			fprintf(fp, "\n");
		}
		res = fclose(fp);
	}	
	return res;
}

Calendar_t* CreateCalendar(unsigned int capacity)
{
	Calendar_t* Calendar = NULL;
	Calendar_t* res = NULL;

	Calendar = malloc(sizeof(Calendar_t));
	if(NULL != Calendar)
	{
		Calendar->noe = 0;
		Calendar->capacity = capacity;
		Calendar->m_arr = malloc(Calendar->capacity * sizeof(mtPtr));
		if(NULL != Calendar->m_arr)
		{
			res = Calendar;
		}
		else
		{
			free(Calendar);
		}
	}
	return res;
}

mtPtr CreateMeeting(float startTime, float endTime, unsigned int roomNum)
{
	mtPtr meeting = NULL;
	mtPtr res = NULL;
	
	if(startTime >= 0.0 && endTime <= 24.0 && endTime > startTime)
	{
		meeting = malloc(sizeof(Meeting_t));
		if(NULL != meeting)
		{
			meeting->startTime = startTime;
			meeting->endTime = endTime;
			meeting->roomNum = roomNum;
			res = meeting;
		}
	}
	return res;
}

int OverlapCheck(Calendar_t* calendar, mtPtr meeting)
{
	int i = 0, res = 0;
	if(calendar->noe != 0)
	{
		for(i = 0; i < calendar->noe; ++i)
		{
			printf("%f %f", calendar->m_arr[i]->startTime, calendar->m_arr[i]->endTime);
			if(meeting->startTime < calendar->m_arr[i]->endTime)
			{				
				if(meeting->endTime > calendar->m_arr[i]->endTime)
				{
					res = -1;
					break;
				}
				if(meeting->endTime > calendar->m_arr[i]->startTime)
				{
					res = -1;
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

int InsertMeeting(Calendar_t* calendar, mtPtr meeting)
{
	mtPtr* tempip;
	int i = 0, res = -1;

	if(NULL != calendar && NULL != meeting)
	{
		if(calendar->noe == calendar->capacity)
		{
			tempip = realloc(calendar->m_arr, calendar->capacity * 2 * sizeof(mtPtr));
			if(NULL != tempip)
			{
				calendar->m_arr = tempip;
				calendar->capacity *= 2;
			}
		}
		
		res = OverlapCheck(calendar, meeting);

		if(-1 != res)
		{
			for(i = calendar->noe; i > res; --i)
			{
				calendar->m_arr[i] = calendar->m_arr[i - 1];
			}
			calendar->m_arr[res] = meeting;
			++(calendar->noe);
		}	
	}
	return res;
}

int FindMeetingIndex(Calendar_t* calendar, float startTime)
{
	int i = 0, res = -1;

	for(i = 0; i < calendar->noe; ++i)
	{
		if((calendar->m_arr[i])->startTime == startTime)
		{
			res = i;
			break;
		}
	}	
	return res;
}

mtPtr FindMeeting(Calendar_t* calendar, float startTime)
{
	int index = 0;
	mtPtr res = NULL;

	if(startTime >= 0.0 && startTime < 24.0 && NULL != calendar)
	{
		index = FindMeetingIndex(calendar, startTime);
		if(-1 != index)
		{
			res = calendar->m_arr[index];
		}
	}
	return res;
}

int Remove(Calendar_t* calendar, float startTime)
{
	int i = 0, index, res = -1;

	if(startTime >= 0.0 && startTime < 24.0 && NULL != calendar)
	{
		index = FindMeetingIndex(calendar, startTime);
		if(-1 != index)
		{
			free(calendar->m_arr[index]);
			for(i = index; i < (calendar->noe) - 1; ++i)
			{
				calendar->m_arr[i] = calendar->m_arr[i + 1];		
			}
			--(calendar->noe);
			res = 0;
		}
	}
	return res;
}

int PrintCalendar(Calendar_t* calendar)
{
	int i = 0, res = -1;
	if(NULL != calendar)
	{
		if(0 == calendar->noe)
		{
			printf("\nNo meetings were found\n");
			res = 0;
		}
		else
		{
			printf("\nMeetings:\n");
			for(i = 0; i < calendar->noe; ++i)
			{
				printf("Start Time: %.2f   ", (calendar->m_arr[i])->startTime);
				printf("End Time: %.2f   "  , (calendar->m_arr[i])->endTime);
				printf("Room Number: %d   " , (calendar->m_arr[i])->roomNum);
				printf("\n");
			}
			printf("\n");
			res = 0;
		}
	}
	return res;
}


void Destroy(Calendar_t* calendar)
{
	int i;
	if(NULL == calendar)
	{
		return;
	}
	for(i = 0; i < calendar->noe; ++i)
	{
		free(calendar->m_arr[i]);
	}
	free(calendar->m_arr);
	free(calendar);
}

