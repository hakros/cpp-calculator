#include <gtest/gtest.h>
#include "../calculator.h"
#include <iostream>

float allowedErrorMargin () {
    return 0.2;
}

TEST(CalculatorTests, Addition) {
    EXPECT_NEAR(4, add(2,2), allowedErrorMargin());
    EXPECT_NEAR(4, add(4,0), allowedErrorMargin());
    EXPECT_NEAR(4, add(6,-2), allowedErrorMargin());
    EXPECT_NEAR(2.3, add(1.2,1.1), allowedErrorMargin());
}

TEST(CalculatorTests, Subtraction) {
    EXPECT_NEAR(4, subtract(6,2), allowedErrorMargin());
    EXPECT_NEAR(4, subtract(4,0), allowedErrorMargin());
    EXPECT_NEAR(8, subtract(6,-2), allowedErrorMargin());
    EXPECT_NEAR(-4, subtract(0,4), allowedErrorMargin());
    EXPECT_NEAR(0, subtract(4,4), allowedErrorMargin());
    EXPECT_NEAR(1.1, subtract(2.3,1.2), allowedErrorMargin());
}

TEST(CalculatorTests, Multiplication) {
    EXPECT_NEAR(4, multiply(2,2), allowedErrorMargin());
    EXPECT_NEAR(0, multiply(2,0), allowedErrorMargin());
    EXPECT_NEAR(-4, multiply(2,-2), allowedErrorMargin());
    EXPECT_NEAR(1, multiply(0.5,2), allowedErrorMargin());
    EXPECT_NEAR(0.4, multiply(0.2,2), allowedErrorMargin());
}

TEST(CalculatorTests, Division) {
    EXPECT_NEAR(1, divide(2, 2), allowedErrorMargin());
    EXPECT_NEAR(2, divide(2, 1), allowedErrorMargin());
    EXPECT_NEAR(-1, divide(2, -2), allowedErrorMargin());
    EXPECT_NEAR(0.5, divide(1, 2), allowedErrorMargin());
    EXPECT_NEAR(5, divide(1, 0.2), allowedErrorMargin());
}

TEST(CalculatorTests, Power) {
    EXPECT_NEAR(4, power(2, 2), allowedErrorMargin());
    EXPECT_NEAR(2, power(2, 1), allowedErrorMargin());
    EXPECT_NEAR(0.25, power(2, -2), allowedErrorMargin());
    EXPECT_NEAR(1, power(1, 2), allowedErrorMargin());
}

int main () {
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}