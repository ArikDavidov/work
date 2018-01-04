#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ReadWriteToFile.h"

#define  MAX_STRING_LENGTH 1024


int PrintLastNLines(FILE *fp, int n){
	int 	*arr = NULL;
	char	str[MAX_STRING_LENGTH];
	int		i = 0, tmpLocation, res = -1;		
	
	if(fp != NULL)
	{
		arr = malloc(n * sizeof(int));
		if(arr != NULL)
		{
			while(1)
			{	
				tmpLocation = ftell(fp);
				fgets(str, MAX_STRING_LENGTH, fp);
				if (feof(fp)) 
				{
					break;
				}
				arr[i % n] = tmpLocation;
				++i;
			}		
			fseek(fp, arr[i % n], 0);
			while(1){		
				fgets(str, MAX_STRING_LENGTH, fp);
				if (feof(fp))
				{
					break;
				}
				fputs(str, stdout);
			}			
			free(arr);
		}
	}
	return res;
}

int LetterFrequencyInFile(FILE *fp){
	int	i = 0, res = -1;
	int	upperCaseLetters['Z' - 'A' + 1] = {0};
	int	lowerCaseLetters['Z' - 'A' + 1] = {0};
	char str[MAX_STRING_LENGTH];
	
	if(fp != NULL){
		while(1){
			fgets(str, MAX_STRING_LENGTH, fp);
			i =0;
			while(str[i] != '\0'){
				if(str[i] >= 'A' && str[i] <= 'Z')
				{
					++(upperCaseLetters[str[i] - 'A']);
				}
				if(str[i] >= 'a' && str[i] <= 'z')
				{
					++(lowerCaseLetters[str[i] - 'a']);
				}
				++i;
			}
			if (feof(fp)) {break;}
		}
		for(i = 0; i < 'Z' - 'A'; ++i){
			if(upperCaseLetters[i] > 0)
			{
				printf("%c %d\n", i + 'A', upperCaseLetters[i]);
			}
			if(lowerCaseLetters[i] > 0)
			{
				printf("%c %d\n", i + 'a', lowerCaseLetters[i]);
			}
		}
		res = 0;
	}	
}
/*
int LetterFrequencyInFile(FILE *fp){
	int	i = 0, res = -1;
	int	upperCaseLetters['Z' - 'A'] = {0};
	int	lowerCaseLetters['Z' - 'A'] = {0};
	char str[MAX_STRING_LENGTH];
	
	if(fp != NULL){
		while(1){
			fgets(str, MAX_STRING_LENGTH, fp);
			i =0;
			while(str[i] != '\0'){
				if(isupper(str[i])
				{
					++(lettersArr[str[i] - 'A']);
				}
				if(islower(str[i]){
					++(lettersArr[str[i] - 'a']);
				}
				++i;
			}
			if (feof(fp)) {break;}
		}
		for(i = 0; i < 'Z' - 'A'; ++i){
			if(upperCaseLetters[i] > 0){
				printf("%c %d\n", i + 'A', upperCaseLetters[i]);
			}
			if(lowerCaseLetters[i] > 0){
				printf("%c %d\n", i + 'a', lowerCaseLetters[i]);
			}
		}
		res = 0;
	}	
}
*/

int WordFrequencyInFile(FILE *fp){
	int	i = 0, res = -1;
	char str[MAX_STRING_LENGTH];
	wordsDA_t* words = NULL;
	
	if(fp != NULL){
		words = CreateDA(128);
		while(1){
			fgets(str, MAX_STRING_LENGTH, fp);

}

wordsDA_t* CreateDA(int capacity){
	wordsDA_t* words = NULL;

	words = malloc(sizeof(wordsDA_t));
	if (words != NULL){
		words->noe = 0;
		words->capacity = capacity;
		words->arr = malloc(words->capacity*sizeof(word));
		if(words->arr != NULL){
			res = words;
		}
		else{
			free(words);
		}
	return words;
}

wordPtr CreateWord(char* str){
	wordPtr word = NULL;
	wordPtr res = NULL;
	
	if(0 != strlen(str)){
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

int Insert(wordsDA_t* words, wordPtr word){
	wordPtr* tempip;
	if(words != NULL && word != NULL){
		if(words->noe == words->capacity){
			tempip = realloc(words->arr, words->capacity*2*sizeof(wordPtr));
			if(tempip != NULL){
				words->arr = tempip;
				words->capacity *=2;
			}

		}
		words->arr[words->noe] = word;
		++(words->noe);
	return 1;
}

void Destroy(wordsDA_t* words){
	int i;
	for(i=0; i<(words->noe); ++i){
		free(words->arr[i]);
	}
	free(words->arr);
	free(words);
}















	

