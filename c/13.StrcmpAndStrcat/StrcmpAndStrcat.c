#include <stdio.h>
#include "StringManipulation.h"

int MyStrcmp(const char *str1, const char *str2){
	int i = 0, res = 0;
	
	if(str1 == NULL){res -= 1;}
	if(str2 == NULL){res += 1;}
	if(str1 != NULL  && str2 != NULL){	
		while(str1[i] - str2[i] ==0){
			if(str1[i] == '\0' || str2[i] == '\0') {break;}
			++i;
		}
		res = str1[i] - str2[i];
	}
	return res;
}

int MyStrcat(const char *str1, const char *str2){
	int i = 0, cont = 1, res = 0;

	while(cont){
		if(str1[i] == '\0' || str2[i] == '\0') {cont = 0;}
		if(str1[i] == str2[i]){
			++i;
			continue;
		}
		else if(str1[i] > str2[i]){
			res = 1;
			break;
		}
		else{
			res = -1;
			break;
		}		
	}
	return res;
}
