#include <gtest/gtest.h>
#include "./task.h"

TEST(OctalBasics, DefaultIsZero) {
    Octal z;
    EXPECT_EQ(z.toString(), "0");
}

TEST(OctalBasics, FromString) {
    Octal a("123");
    EXPECT_EQ(a.toDecimal(), 83); // 1*64 + 2*8 + 3
}

TEST(OctalBasics, RejectsBadDigits) {
    EXPECT_THROW(Octal("9"), std::invalid_argument);
    EXPECT_THROW(Octal("8"), std::invalid_argument);
    EXPECT_THROW(Octal("a"), std::invalid_argument);
}

TEST(Addition, CarryWorks) {
    Octal a("7"), b("1");
    Octal c = a.add(b);
    EXPECT_EQ(c.toString(), "10");
}

TEST(Addition, LongCarry) {
    Octal res = Octal("777").add(Octal("1"));
    EXPECT_EQ(res.toString(), "1000");
}
TEST(Subtraction, SimpleSub) {
    Octal diff = Octal("10").subtract(Octal("1"));
    EXPECT_EQ(diff.toString(), "7");
}

TEST(Subtraction, NoNegatives) {
    EXPECT_THROW(Octal("5").subtract(Octal("10")), std::underflow_error);
}

TEST(Comparison, EqualNumbers) {
    Octal x("123"), y("000123");
    EXPECT_TRUE(x.equals(y));
}

TEST(Comparison, GreaterWorks) {
    // 100 (oct) = 64, 77 (oct) = 63
    EXPECT_TRUE(Octal("100").greater(Octal("77")));
    EXPECT_FALSE(Octal("10").greater(Octal("20")));
}

TEST(Comparison, LessWorks) {
    EXPECT_TRUE(Octal("10").less(Octal("20")));
    EXPECT_FALSE(Octal("100").less(Octal("77")));
}

TEST(Normalization, LeadingZerosGone) {
    Octal a("00042");
    EXPECT_EQ(a.toString(), "42");
}

TEST(Subtraction, ZeroMinusZero) {
    Octal z = Octal("0").subtract(Octal("0"));
    EXPECT_EQ(z.toString(), "0");
}

TEST(Addition, AddZero) {
    Octal a("123");
    Octal b = a.add(Octal("0"));
    EXPECT_EQ(b.toString(), "123");
}