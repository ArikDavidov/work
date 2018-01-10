#ifndef __UNCOPYABLE__
#define __UNCOPYABLE__


class uncopyable
{
protected:
	uncopyable() {}
	~uncopyable() {}b

private:  // emphasize the following members are private
	uncopyable(const uncopyable&);
	uncopyable& operator=(const uncopyable&);
};


#endif // __UNCOPYABLE__
