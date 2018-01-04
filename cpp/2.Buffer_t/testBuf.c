#include "Buffer_t.h"
#include "mu_test.h"

#include <stdio.h>
#include <string.h>


UNIT(DefaultCTOR)
	Buffer_t string;
	ASSERT_THAT(0 == strlen(string.GetString()));
END_UNIT

UNIT(SetAndGet)
	Buffer_t string;
	string.SetString("Zero Bug Approach");
	ASSERT_THAT(0 == strcmp(string.GetString(), "Zero Bug Approach"));
END_UNIT

UNIT(CTORFromCharPtr)
	Buffer_t string("Zero Bug Approach");
	ASSERT_THAT(0 == strcmp(string.GetString(), "Zero Bug Approach"));
END_UNIT


TEST_SUITE(framework test)
	TEST(DefaultCTOR)
	TEST(SetAndGet)
	TEST(CTORFromCharPtr)
	TEST(CTORFromCharPtrNull)
END_SUITE











	
