#include "SafeQueue.h"

#include <iostream>
//using namespace std;

int main()
{
	SafeQueue<int> queue;
	
	queue.Push(5);
	
	std::cout << queue.Pop() << std::endl;
	
	return 0;
}


