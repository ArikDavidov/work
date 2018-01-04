#ifndef __UNCOPYABLE__
#define __UNCOPYABLE__


class uncopyable
{
protected:
	uncopyable() {}
	~uncopyable() {}

private:  // emphasize the following members are private
	uncopyable(const uncopyable&);
	const uncopyable& operator=(const uncopyable&);
};

#endif // !__UNCOPYABLE__
