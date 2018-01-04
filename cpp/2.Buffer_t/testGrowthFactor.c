
#include <iostream>




/* This over-allocates proportional to the list size, making room
 * for additional growth.  The over-allocation is mild, but is
 * enough to give linear-time amortized behavior over a long
 * sequence of appends() in the presence of a poorly-performing
 * system realloc().
 * The growth pattern is:  0, 4, 8, 16, 25, 35, 46, 58, 72, 88, ...
 */
CalculateCapacuty(i)
{
    capacity = (_len >> 3) + (_len < 9 ? 3 : 6);
}   
    
int main()
{
	for (i = 0; i < count; i += 1)
	{
		capacity = CalculateCapacuty(i);
		cout << 
	}
	
	return 0;
} 
    
    
