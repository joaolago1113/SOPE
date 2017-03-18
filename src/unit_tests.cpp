
extern "C" {
#include "strings.h"
}
#include "gtest/gtest.h"



TEST(strings, str_length)
{
	EXPECT_EQ(str_length("hi"),2);
	EXPECT_EQ(str_length(""),0);

}

TEST(strings, streq)
{
	EXPECT_EQ(streq("Hell, ", "Hello",2),true);
	EXPECT_EQ(streq("Hell, ", "Hello",5),false);
}
