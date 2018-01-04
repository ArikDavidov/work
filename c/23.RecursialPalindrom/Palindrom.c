

unsigned int IsPalindrom(char* _arr, unsigned int _length)
{
	if (1 == _length)
	{
		return 1;
	}
	if (0 == _length)
	{
		return 1;
	}
	if (_arr[0] != _arr[_length - 1])
	{
		return = 1;
	}
		
	return ((_arr[0] == _arr[_length - 1]) ? 1 : 0) * IsPalindrom(_arr + 1 , _length -2);
}





