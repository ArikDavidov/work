#include "Event.h"
#include "SafeQueue.h"


#include <iostream>

typedef std::tr1::shared_ptr<Event> spEvent_t;


class foo
{
public:
    void Print(spEvent_t _sp)
    {
        std::cout << _sp->Topic() << std::endl;
    }
};


int main()
{
    spEvent_t sp(new Event("CATS", "1", "13"));
    
    SafeQueue<spEvent_t> q;
    q.Push(sp);
    
    foo f;
    f.Print(q.Pop());
    
    return 0;
}


