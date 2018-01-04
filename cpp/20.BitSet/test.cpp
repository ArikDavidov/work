#include "BitSet.h"
#include "mu_test.h"

#include <cstdio>
#include <iostream>
using namespace advcpp;


UNIT(UnsignedInt)
    BitSet<64, unsigned int> bs;
    ASSERT_THAT(0 == bs.Count());
    bs.Set(2, 1);
    ASSERT_THAT(1 == bs.IsBitOn(2));
    bs.Set(60, 1);
    ASSERT_THAT(1 == bs.IsBitOn(60));
END_UNIT

UNIT(Count)
    BitSet<128, unsigned int> bs;
    ASSERT_THAT(0 == bs.Count());
    bs.Set(2, 1);
    bs.Set(60, 1);
    ASSERT_THAT(2 == bs.Count());
    bs.Set(2, 0);
    ASSERT_THAT(1 == bs.Count());
END_UNIT

UNIT(Default)
    BitSet<5> bs;
    bs.Set(2, 1);
    ASSERT_THAT(1 == bs.IsBitOn(2));
    bs.Set(2, 0);
    ASSERT_THAT(0 == bs.IsBitOn(2)); 
END_UNIT

UNIT(UnsignedLong)
    BitSet<5, unsigned long> bs;
    bs.Set(2, 1);
    ASSERT_THAT(1 == bs.IsBitOn(2));
    bs.Set(2, 0);
    ASSERT_THAT(0 == bs.IsBitOn(2));
END_UNIT

UNIT(Flip)
    BitSet<16, unsigned int> bs;
    bs.Set(2, 1);
    bs.Flip();
    ASSERT_THAT(15 == bs.Count());
END_UNIT

UNIT(Any)
    BitSet<16, unsigned int> bs;
    ASSERT_THAT(false == bs.Any());
    bs.Set(2, 1);
    ASSERT_THAT(true == bs.Any());
END_UNIT

UNIT(All)
    BitSet<4, unsigned int> bs;
    bs.Set(0, 1);
    bs.Set(1, 1);
    bs.Set(2, 1);
    ASSERT_THAT(false == bs.All());
    bs.Set(3, 1);
    ASSERT_THAT(true == bs.All());
END_UNIT

UNIT(None)
    BitSet<4, unsigned int> bs;
    ASSERT_THAT(true == bs.None());
    bs.Set(0, 1);
    ASSERT_THAT(false == bs.None());
END_UNIT

UNIT(Complement)
    BitSet<16, unsigned int> bs;
    bs.Set(15, 1);
    bs = ~bs;
    ASSERT_THAT(15 == bs.Count());
END_UNIT

UNIT(AndEql)
    BitSet<4, unsigned int> bs1;
    bs1.Set(0, 1);
    bs1.Set(3, 1);
    BitSet<4, unsigned int> bs2;
    bs2.Set(0, 1);
    bs1 &= bs2;
    ASSERT_THAT(1 == bs1.Count());
END_UNIT

UNIT(ConstSubscript)
    const BitSet<64, unsigned int> bs;
    ASSERT_THAT(false == bs[2]);
END_UNIT

UNIT(Subscript)
    BitSet<64, unsigned int> bs;
    ASSERT_THAT(bs[2] == false);
    bs.Set(2, 1);
    ASSERT_THAT(bs[2] == true);
    bs[60] = true;
    ASSERT_THAT(1 == bs[60]);
    bs.Set(2, 0);
    ASSERT_THAT(0 == bs[2]);
END_UNIT

UNIT(OpOr)
    BitSet<4, unsigned int> bs1;
    bs1.Set(0, 1);
    bs1.Set(3, 1);
    BitSet<4, unsigned int> bs2;
    bs2.Set(0, 1);
    BitSet<4, unsigned int> bs3(bs1 | bs2);
    ASSERT_THAT(2 == bs3.Count());
END_UNIT

UNIT(LeftShiftEql)
    BitSet<64, unsigned int> bs;
    bs[30] = true;
    bs[62] = true;
    bs <<= 3;
    ASSERT_THAT(1 == bs[33]);
    ASSERT_THAT(1 == bs.Count());
END_UNIT

UNIT(LeftShift)
    BitSet<64, unsigned int> bs;
    bs[30] = true;
    bs[62] = true;
    BitSet<64, unsigned int> bs1 = bs << 3;
    ASSERT_THAT(1 == bs1[33]);
    ASSERT_THAT(1 == bs1.Count());
END_UNIT

UNIT(RightShiftEql)
    BitSet<64, unsigned int> bs;
    bs[2] = true;
    bs[33] = true;
    bs >>= 3;
    ASSERT_THAT(1 == bs[30]);
    ASSERT_THAT(1 == bs.Count());
END_UNIT
   
UNIT(RightShift)
    BitSet<64, unsigned int> bs;
    bs[2] = true;
    bs[33] = true;
    BitSet<64, unsigned int> bs1 = bs >> 3;
    ASSERT_THAT(1 == bs1[30]);
    ASSERT_THAT(1 == bs1.Count());
END_UNIT
    
 
//    std::cout << bs << std::endl;

TEST_SUITE(framework test)
    TEST(UnsignedInt)
    TEST(Count)
    TEST(Default)
    TEST(UnsignedLong)
    TEST(Flip)
    TEST(Any)
    TEST(All)
    TEST(None)
    TEST(Complement)
    TEST(AndEql)
    TEST(ConstSubscript)
    TEST(Subscript)
    TEST(OpOr)
    TEST(LeftShiftEql)
    TEST(LeftShift)
    TEST(RightShiftEql)
    TEST(RightShift)
END_SUITE


