#include "String_t.h"
#include "Buffer.h"
#include "mu_test.h"

#include <cstdio>
#include <iostream>
using namespace advcpp;


UNIT(BufferCTOR)
    Buffer<char> buf(16);
    ASSERT_THAT(16 == buf.Size());
    ASSERT_THAT(16 == buf.Capacity());
END_UNIT

UNIT(StringCTOR)
    String_t<char> str("Zero bug");
    ASSERT_THAT(8 == str.Length());
END_UNIT

//UNIT(SetAndGet)
//  String_t string;
//  string.SetString("Zero Bug Approach");
//  ASSERT_THAT(0 == strcmp(string.GetString(), "Zero Bug Approach"));
//END_UNIT

TEST_SUITE(framework test)
    TEST(BufferCTOR)
    TEST(StringCTOR)
END_SUITE


