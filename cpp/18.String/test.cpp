#include "String_t.h"
#include "Buffer.h"
#include "mu_test.h"

#include <cstdio>
#include <iostream>
using namespace advcpp;


UNIT(BufferCTOR)
    Buffer<char> buf;
    ASSERT_THAT(0 == buf.Size());
    ASSERT_THAT(16 == buf.Capacity());
    ASSERT_THAT(16 == buf.DefaultCapacity());
    buf.DefaultCapacity(32);
    ASSERT_THAT(32 == buf.DefaultCapacity());
END_UNIT

UNIT(StringCTOR)
    String_t str("Zero bug");
    ASSERT_THAT(8 == str.Size());
    ASSERT_THAT(16 == str.Capacity());
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


