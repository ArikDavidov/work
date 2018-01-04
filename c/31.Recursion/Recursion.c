#include <stdio.h>
#include <string.h>

void StarsIncrease(unsigned  int n)
{
	int i;
	
	if (0 == n)
	{
		return;
	}
	StarsIncrease(n - 1);
	for (i = 0; i < n; ++i)
	{
		printf("*");
	}
	printf("\n");
}

void StarsDecrease(unsigned  int n)
{
	int i;
	
	if (0 == n)
	{
		return;
	}
	for (i = 0; i < n; ++i)
	{
		printf("*");
	}
	printf("\n");
	
	StarsDecrease(n - 1);
}

double Average(int* _arr, int _size, int _count, int _sum)
{
	if (0 == _size)
	{
		return (double)_sum / _count;
	}
	
	return Average(_arr + 1, _size - 1, _count + 1, _sum + _arr[0]);	
}

char LastCharInString(char* _str)
{
	if ('\0' == _str[0])
	{
		return _str[-1];
	}	
	return LastCharInString(_str + 1);
}

void RecursiveMultTabel(int _counter, int _columns)
{
	if (0 == _counter)
	{
		return;
	}	
	RecursiveMultTabel(_counter - 1, _columns);	
	if (0 == (_counter % _columns))
	{
		printf("\n");
	}
	else
	{
		/* Rows * columns*/
		printf(" %3d", (_counter % _columns) * ((_counter / _columns) + 1));
	}	
}

void MultTabel(int _rows, int _columns)
{
	/* One more column to make room for "\n" in the end of each row*/
	++_columns;
	RecursiveMultTabel(_rows * _columns, _columns);
}

void swap(char* _x, char* _y)
{
	char temp;

	temp = *_x;
	*_x = *_y;
	*_y = temp;
}

int RecursiveStringReverse(char* _str, int _length)
{	
	if (1 == _length)
	{
		return 0;
	}
	if (0 == _length)
	{
		return 0;
	}
	swap(_str, &_str[_length - 1]);
	
	return RecursiveStringReverse(_str + 1, _length - 2);
}

int PrintStringPermutations(char* _str, int _len, int _permCounter, int _index)
{
	if (_len -1 == _index)	/* Last index */
	{
		printf("%s\n", _str);
		return 0;
	}
	/* On each index the number of permutations is len - index */
	PrintStringPermutations(_str, _len, _len - (_index + 1), _index + 1);
	/* Complition of permutations in the current index. */
	if (1 == _permCounter)
	{
		return 0;
	}
	RecursiveStringReverse(&_str[_index], _len - _index);

	return PrintStringPermutations(_str, _len, _permCounter - 1, _index);
}

int main()
{
	char str[] = "ABCD";
	/* 	
	int arr[] = {1, 2, 3, 6, 11, 155};
	int rows, columns;

	StarsIncrease(5);
	printf("\n");
	StarsDecrease(8);
	printf("\n");
	printf("Please enter size:\n")
	scanf("%d", &size);
	printf("Average: %.2f\n", Average(arr, 6, 0, 0));
	printf("The last character is: %c\n\n", LastCharInString(str));
	printf("Please enter rows:\n");
	scanf("%d", &rows);
	printf("Please enter columns:\n");
	scanf("%d", &columns);	 
	MultTabel(rows, columns);
	*/
	PrintStringPermutations(str, strlen(str), strlen(str), 0);
	
	
	return 0;
}






