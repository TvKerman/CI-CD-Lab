#include "../src/BigInt.h"
#include <gtest/gtest.h>

TEST(BigIntTest, Addition) {
    BigInt a("9999");
    BigInt b("1");
    EXPECT_EQ((a + b).toString(), "10000");
}

TEST(BigIntTest, Subtraction) {
    BigInt a("10000");
    BigInt b("1");
    EXPECT_EQ((a - b).toString(), "9999");
}

TEST(BigIntTest, Multiplication) {
    BigInt a("123456789");
    BigInt b("2");
    EXPECT_EQ((a * b).toString(), "246913578");
}

TEST(BigIntTest, Compare) {
    EXPECT_TRUE(BigInt("10") > BigInt("2"));
    EXPECT_TRUE(BigInt("2") < BigInt("10"));
}
