#ifndef TIME_AND_DATE_H
#define TIME_AND_DATE_H

#include<stdlib.h>
#include<ctype.h>

		
int ReverseString(char *string);
/*The function reverses a string by swaping values of the first and last characters.
and then advancing the pointers (the left - one char to the right, and the right - one char to the left).
returns:
 0  - The function succeeded.
-1  - Error.
*/

int IsPalindrom(char *string);
/*The function checks if a string is a palindrom by comparing values of the first and last characters
  and then advancing the pointers (the left - one char to the right, and the right - one char to the left).
returns:
 1  - If it's a palindrom.
 0  - If it's not a palindrom.
-1  - Error.
*/

int MyAToI(char *string);	
/*The function converts a string into an integers.
Leading blank chars are skiped.
trailing illegal chars are ignored.
returns:
 0  - Conversion cannot be made.
int - The result of the conversion.
-1  - Error.
*/
char* MyIToA(int integer, char *string, int base);
/*The function converts an integer into a string using the specified base,
  and stores the result in the array given by string parameter.
If base is 10 and value is negative, the resulting string is preceded with "-".
returns:
char* - The result of the conversion
NULL - Error.
*/
#endif


