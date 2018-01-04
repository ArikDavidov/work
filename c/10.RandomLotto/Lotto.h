#ifndef LOTTO_H
#define LOTTO_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_NUM 49
#define NUM_OF_RANDOM_NUMS 6
#define ROWS 5
#define COLUMNS 10

int GenerateRandNums(int* randNumArr, unsigned int namOfRandomNums);
/*Generates 6 random numbers betwen 1 and MAX_NUM.
  All 6 number are diferent from each other.
  Returns pointer to the array. */


int PrintRandNums(int* randNumArr, unsigned int namOfRandomNums);
/*Prints the array of numbers generatet by the function PrintInLottoFormat.
  Recives an array (whith it's size) to print and returns 0 if printed succesfuly.
  Otherwise returns -1.  */

int PrintLottoCard(int* randNumArr,unsigned int namOfRandomNums);
/* Recives an array (whith it's size) and prints it in a Lotto card format.
   returns 0 if printed succesfuly, otherwise returns -1.
   Example:

  1 2 3 4 5 6 7 8 9 10
0 + - - - - - - - - -

1 - - - + - - - - - -

2 - - + - + - - - + -

3 - - + - - - - - - -

4 - - - - - - - - -  


In this example the random numbers were:  1 23 14 29 25 33

*/

#endif


