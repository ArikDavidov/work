#include "EventFilter.h"
#include "mu_test.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>



//UNIT(a)
//    EventFilter a("Cats", "3", "42");
//    EventFilter b("Cats", "3", "42");
//	ASSERT_THAT(a == b);
//	ASSERT_THAT(!(a < b));
//	ASSERT_THAT(!(b < a));
//END_UNIT

//UNIT(b)
//    EventFilter a("Cats", "3", "42");
//    EventFilter b("Cats", "42", "3");
//	ASSERT_THAT(!(a == b));
//	ASSERT_THAT((a < b));
//	ASSERT_THAT(!(b < a));
//END_UNIT

//UNIT(c)
//    EventFilter a("", "3", "42");
//    EventFilter b("Cats", "42", "3");
//	ASSERT_THAT(!(a == b));
//	ASSERT_THAT((a < b));
//	ASSERT_THAT(!(b < a));
//END_UNIT

//UNIT(d)
//    EventFilter a("", "", "");
//    EventFilter b("Cats", "42", "3");
//	ASSERT_THAT(a == b);
//	ASSERT_THAT(!(a < b));
//	ASSERT_THAT(!(b < a));
//END_UNIT

//UNIT(e)
//    EventFilter a("c", "42", "");
//    EventFilter b("c", "42", "3");
//	ASSERT_THAT(a == b);
//	ASSERT_THAT(!(a < b));
//	ASSERT_THAT(!(b < a));
//END_UNIT

UNIT(f)
    std::set<EventFilter*> set;
    
    EventFilter* a = new EventFilter("c", "42", "");
    set.insert(a);
    EventFilter* b = new EventFilter("c", "42", "3");
    set.insert(b);
    EventFilter* c = new EventFilter("c", "42", "");
    set.insert(c);
    EventFilter* d = new EventFilter("", "", "");
    set.insert(d);
    EventFilter* e = new EventFilter("c", "41", "");
    set.insert(e);
    EventFilter* f = new EventFilter("xxx", "", "");
    set.insert(f);
    EventFilter* g = new EventFilter("c", "42", "");
    set.insert(g);
    EventFilter* h = new EventFilter("", "", "");
    set.insert(h);
    
    for (std::set<EventFilter*>::iterator it = set.begin(); it != set.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    
//    EventFilter a1("c", "42", "1");
END_UNIT
//    EventFilter b1("c", "42", "3");
//    EventFilter c1("c", "42", "11");
//    EventFilter e1("c", "41", "2");
//    EventFilter f1("xxx", "xx", "xx");    
//    EventFilter g1("c", "42", "xxx");
//    EventFilter h1("11", "12", "d");


TEST_SUITE(framework test)
//	TEST(a)
//	TEST(b)
//	TEST(c)
//	TEST(d)
//	TEST(e)
    TEST(f)
END_SUITE

