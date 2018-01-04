#include <string.h>
#include <stdio.h>
#include "StringManipulation.h"

int ReverseString(char *string){
	char tmpChar;
	int i, stringLength = 0, res = -1;
	
	if(string != NULL){
		stringLength = strlen(string);
		if(stringLength > 0){
			for(i = 0; i < stringLength / 2; ++i){
				tmpChar = string[stringLength -1 - i];		/*Swaping values of left and right pointers*/	
				string[stringLength -1 - i] = string[i];
				string[i] = tmpChar;
			}					 		/*Advancing pointers*/
			res = 0;
		}
	}
	return res;
}

int IsPalindrom(char *string){
	int i, stringLength = 0, res = -1;
	
	if(string != NULL){
		stringLength = strlen(string);
		if(stringLength > 0){
			for(i = 0; i < stringLength / 2; ++i){
				if(string[i] != string[stringLength -1 - i]){ 	/*comparing values of right and left pointers*/
					res = 0;
					break;
				}
				else{res = 1;}
			}					/*Advancing pointers*/				
		}
	}
	return res;
}

int MyAToI(char *string)
{
	int i = 0, stringLength = 0, firstNonBlank = 0, res = 0;
	
	if(string != NULL)
	{
		stringLength = strlen(string);
		if(stringLength > 0)
		{
			for(i = 0; i < stringLength; ++i)
			{
				/*Skip leading blanks*/
				if(isspace(string[i])) 
				{
					++firstNonBlank;
				}
				else
				{
					break;
				}
			}
			if(string[i] == '+' || string[i] == '-') 
			{
				++i;
			}
			while(i < stringLength)
			{
				if(string[i] >= '0' && string[i] <= '9')
				{
					res *= 10;
					/*Subtructing char '0' from char representing an int, will result the int value of that char*/
					res += string[i] - '0';	
					++i;
				}
				/*Ignore traling illegal characters*/
				else
				{
					break;
				}
			}
		}	
	}
	if(string[firstNonBlank] == '-') {res *= -1;}
	return res;
}

char* MyIToA(int integer, char *string, int base)
{
	int i = 0, polarity = 1, digit;

	/*The base must be between 2 and 36*/
	if(string != NULL  && base <= 36 && base > 0)
	{ 
		if(integer == 0) {string[0] = '0';}
		/*Converting to unsigned*/
		if(integer < 0)
		{				
			integer *= -1;
			polarity = -1;
		}
		/*Getting the digits from right to left*/
		while(integer > 0)
		{				
			digit = integer % base;
			if(digit < 10)
			{
				string[i] = digit + '0';			
			}
			else
			{
				string[i] = digit - 10 + 'a';
			}
			integer /= base;
			++i;
		}
		/*If base is 10 and value is negative, the resulting string is preceded with "-" */
		if(base == 10 && polarity == -1)
		{	
			string[i] = '-';
			++i;
		}
		string[i] = '\0';
		/*Because we got the digits from right to left*/
		ReverseString(string);	
	}
	return string;
}

