#include "String_t.h"
#include "mu_test.h"

#include <stdio.h>
#include <string.h>


UNIT(DefaultCTOR)
	String_t string;
	ASSERT_THAT(0 == strlen(string.GetString()));
END_UNIT

UNIT(SetAndGet)
	String_t string;
	string.SetString("Zero Bug Approach");
	ASSERT_THAT(0 == strcmp(string.GetString(), "Zero Bug Approach"));
END_UNIT

UNIT(CTORFromCharPtr)
	String_t string("Zero Bug Approach");
	ASSERT_THAT(0 == strcmp(string.GetString(), "Zero Bug Approach"));
END_UNIT

UNIT(CTORFromCharPtrNull)
	String_t string(NULL);
	ASSERT_THAT(0 == strlen(string.GetString()));
END_UNIT

UNIT(CopyCTOR)
	String_t firstString("Zero Bug Approach");
	String_t secondString(firstString);
	ASSERT_THAT(0 == strcmp(secondString.GetString(), "Zero Bug Approach"));
END_UNIT

UNIT(EqualityOperator)
	String_t firstString("Zero Bug Approach");
	String_t secondString("42");
	firstString = secondString;
	ASSERT_THAT(0 == strcmp(firstString.GetString(), "42"));
END_UNIT

UNIT(Length)
	String_t string("Zero Bug Approach");
	ASSERT_THAT(17 == string.Length());
END_UNIT

UNIT(Upper)
	String_t string("Zero Bug Approach");
	string.Upper();
	ASSERT_THAT(0 == strcmp(string.GetString(), "ZERO BUG APPROACH"));
END_UNIT

UNIT(Lower)
	String_t string("Zero Bug Approach");
	string.Lower();
	ASSERT_THAT(0 == strcmp(string.GetString(), "zero bug approach"));
END_UNIT

UNIT(Contains)
	String_t firstString("Zero Bug Approach");
	String_t secondString("Bug");
	String_t thirdString("Approachhhh");
	ASSERT_THAT(1 == firstString.Contains(secondString));
	ASSERT_THAT(0 == firstString.Contains(thirdString));
END_UNIT

UNIT(PrependFromCharPtr)
	String_t string("ug Approach");
	string.Prepend("Zero B");
	ASSERT_THAT(0 == strcmp(string.GetString(), "Zero Bug Approach"));
END_UNIT

UNIT(PrependFromString)
	String_t firstString("ug Approach");
	String_t secondString("Zero B");
	firstString.Prepend(secondString);
	ASSERT_THAT(0 == strcmp(firstString.GetString(), "Zero Bug Approach"));
END_UNIT

UNIT(SqareBracketsOperator)
	String_t string("Zero Bug Approach");
	ASSERT_THAT('r' == string[2]);
	ASSERT_THAT('\0' == string[32]);
END_UNIT

UNIT(FindFirst)
	String_t string("Zero Bug Approach");
	ASSERT_THAT(3 == string.FindFirst('o'));
	ASSERT_THAT(17 == string.FindFirst('j'));
END_UNIT

UNIT(FindLast)
	String_t string("Zero Bug Approach");
	ASSERT_THAT(13 == string.FindLast('o'));
	ASSERT_THAT(17 == string.FindFirst('j'));
END_UNIT
/*
UNIT(ParenthesesOperator)
	String_t string("Zero Bug Approach");
	String_t newString = string(5, 7);
	ASSERT_THAT(strcmp("Bug App", newString.GetString());
END_UNIT
*/

TEST_SUITE(framework test)
	TEST(DefaultCTOR)
	TEST(SetAndGet)
	TEST(CTORFromCharPtr)
	TEST(CTORFromCharPtrNull)
	TEST(CopyCTOR)
	TEST(EqualityOperator)
	TEST(Length)
	TEST(Upper)
	TEST(Lower)
	TEST(Contains)
	TEST(PrependFromCharPtr)
	TEST(PrependFromString)
	TEST(SqareBracketsOperator)
	TEST(FindFirst)
	TEST(FindLast)
END_SUITE











