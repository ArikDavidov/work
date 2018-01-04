#include <stdio.h>
#include "mu_test.h"
#include "SharedPtr.h"

using namespace advcpp;

UNIT(DefaultCtor)
{
	SharedPtr<int> sharedPtr;
	ASSERT_THAT(true);
}
END_UNIT

UNIT(NormalCtor)
{
	int* ptr = new int(7);
	SharedPtr<int> sharedPtr(ptr);
	
	ASSERT_THAT(sharedPtr.Ptr() == ptr);
	ASSERT_THAT(sharedPtr.Count() == 1);
}
END_UNIT

UNIT(CopyCtor)
{
	SharedPtr<int> sharedPtr(new int(7));
	
	{
		SharedPtr<int> secondPtr = sharedPtr;
		ASSERT_THAT(sharedPtr.Ptr() == secondPtr.Ptr());
		ASSERT_THAT(sharedPtr.Count() == 2);
	}
	
	ASSERT_THAT(sharedPtr.Count() == 1);
}
END_UNIT

UNIT(Assignment)
{
	SharedPtr<int> firstPtr;
	{
		SharedPtr<int> secondPtr(new int(7));
		firstPtr = secondPtr;
		ASSERT_THAT(secondPtr.Ptr() == firstPtr.Ptr());
		ASSERT_THAT(firstPtr.Count() == 2);
		ASSERT_THAT(secondPtr.Count() == 2);
		{
			SharedPtr<int> thirdPtr;
			thirdPtr = secondPtr;
			ASSERT_THAT(firstPtr.Ptr() == thirdPtr.Ptr());
			ASSERT_THAT(thirdPtr.Count() == 3);
		}
		ASSERT_THAT(secondPtr.Count() == 2);
		ASSERT_THAT(firstPtr.Count() == 2);
	}
	ASSERT_THAT(firstPtr.Count() == 1);
}
END_UNIT

UNIT(Dereference)
{
	SharedPtr<int> sharedPtr(new int(7));
	SharedPtr<int> secondPtr = sharedPtr;
	
	ASSERT_THAT(*sharedPtr == 7);
	ASSERT_THAT(*secondPtr == 7);
	
}
END_UNIT

class Person
{
public:
	Person() : m_age(7) {}
	int m_age;
};

UNIT(Arrow)
{
	
	SharedPtr<Person> sharedPtr(new Person);
	SharedPtr<Person> secondPtr = sharedPtr;
	
	ASSERT_THAT(sharedPtr->m_age == 7);
	ASSERT_THAT(secondPtr->m_age == 7);
}
END_UNIT
// ----------------------

TEST_SUITE(SharedPtr)

	TEST(DefaultCtor)
	TEST(NormalCtor)
	TEST(CopyCtor)
	TEST(Assignment)
	TEST(Dereference)
	TEST(Arrow)

END_SUITE



