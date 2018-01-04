#ifndef __RECURSION_H__
#define __RECURSION_H__

int* BinarySearch(int* _lowPtr, int* _highPtr, int _searchValue);
/*
Recursive vanction that preforms binary search in sorted array.
Parameters:
_lowPtr      - Pointer to the lowest value in the array.
_highPtr     - Pointer to the highest value in the array.
_searchValue - The searched value.
Returns:
int* - Pointer to the searched value.
NULL - If error ocured or the value was not found.
*/
int RecursiveStringReverse(char* _str, unsigned int _length);
/*
Recursive function that reverses a string.
Parameters:
_str    - Pointer to a string terminated by '\0'.
_length - String length.
Returns:
0 - Success.
*/
void Hanoi(unsigned int _numberOfDiscks);
/*

*/

int EightQueens(int* _arr, int _currentRow, int _currentColumn);
/* Recursive function that finds solutions to Eight Queens problem. 
the function can start from any starting position (wich is not a solution) and find the next solution.
Parameters:
_arr           - each int in the array represent the location of the queen in the corresponding row.
_currentRow    - row index to wich the function is trying to insert the next queen.
_currentColumn - column index to wich the function is trying to insert the next queen.
Returns:
1 - Success.
0 - Failure.
*/
void PrintSolution(int* _arr, int  _solutionNumber);
/*
Prints the solution of EightQueens function.
Parameters:
_arr - Contains integers representing queens' locations on the Chess board.
	   Cannot be NULL.
_solutionNumber - The number of the current solution from 0 to NUMBER_OF_SOLUTIONS -1.
Example:

Solution 91:
 7 3 0 2 5 1 6 4

  0 1 2 3 4 5 6 7
0|_|_|_|_|_|_|_|Q|
1|_|_|_|Q|_|_|_|_|
2|Q|_|_|_|_|_|_|_|
3|_|_|Q|_|_|_|_|_|
4|_|_|_|_|_|Q|_|_|
5|_|Q|_|_|_|_|_|_|
6|_|_|_|_|_|_|Q|_|
7|_|_|_|_|Q|_|_|_|
                             
*/
#endif  /* #ifndef __RECURSION_H__ */



