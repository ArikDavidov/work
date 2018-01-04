

unsigned int Factorial(unsigned int _n)
{
	if(0 == _n)
	{
		return 1;
	}	
	return Factorial(_n - 1) * _n;
}

unsigned int Fib(unsigned int _n)
{
	if(0 == _n)
	{
		return 0;
	}
	if(1 == _n)
	{
		return 1;
	}	
	
	return Fib(_n - 1) + Fib(_n - 2);
}










