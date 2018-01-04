#ifndef READ_WRITE_TO_FILE_H
#define READ_WRITE_TO_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char* str;
	int Frequency;
}word_t;

typedef word_t* wordPtr;

typedef struct{
	wordPtr arr;
	int capacity;
	int noe;
}wordsDA_t;

int PrintLastNLines(FILE *fp, int n);
int LetterFrequencyInFile(FILE *fp);
int WordFrequencyInFile(FILE *fp);
wordsDA_t* CreateDA(int capacity);
int Insert(wordsDA_t* words, wordPtr word);
void Destroy(wordsDA_t* words);
	

#endif
