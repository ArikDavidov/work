

int Add(int _a, int* _b, int* const _c)
{
	*_b += _a + *_c;
	
	return 0;
}

int main()
{
	int const a = 1;
	int* b;
	int d = 2;
	int* c = &d;
	
	b = &a;
	Add(a, b, c);
	
	return 0;
}


