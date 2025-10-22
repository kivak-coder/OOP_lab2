#include "gtest/gtest.h"
#include "../include/five.hpp"

TEST(FiveClass, DefaultConstructor) {
    Five num;
    EXPECT_EQ(num.getSize(), 1);
    EXPECT_EQ(num.getDigit(0), 0);
}

TEST(FiveClass, StringConstructor) {
    Five num("1234");
    EXPECT_EQ(num.getSize(), 4);
    Five num2("10020320");
    EXPECT_EQ(num2.getSize(), 8);
}

TEST(FiveClass, StringConstructorInvalid) {
    EXPECT_THROW(Five num("167"), std::invalid_argument);
}

TEST(FiveClass, CopyConstructor) {
    Five num1("123");
    Five num2(num1);
    EXPECT_EQ(num1.getString(), num2.getString());
}

TEST(FiveClass, AssignmentOperator) {
    Five num1("123");
    Five num2;
    num2 = num1;
    EXPECT_EQ(num1.getString(), num2.getString());
}

TEST(FiveClass, Addition) {
    Five num1("12");
    Five num2("3");
    Five num3("1010");
    Five num4("404123");
    Five result1 = num1 + num2;
    Five result2 = num1 + num3;
    Five result3 = num1 + num4;
    Five result4 = num3 + num4;
    Five result5 = num2 + num4;

    EXPECT_EQ(result1.getString(), "20"); 
    EXPECT_EQ(result2.getString(), "1022"); 
    EXPECT_EQ(result3.getString(), "404140"); 
    EXPECT_EQ(result4.getString(), "410133"); 
    EXPECT_EQ(result5.getString(), "404131"); 
}

TEST(FiveClass, Subtraction) {
    Five num1("20");
    Five num2("3");
    Five num3("1010");
    Five num4("404123");
    Five result1 = num1 - num2;
    Five result2 = num3 - num2;
    Five result3 = num4 - num2;
    Five result4 = num4 - num3;

    EXPECT_EQ(result1.getString(), "12"); 
    EXPECT_EQ(result2.getString(), "1002"); 
    EXPECT_EQ(result3.getString(), "404120"); 
    EXPECT_EQ(result4.getString(), "403113"); 
}

TEST(FiveClass, SubtractionNegative) {
    Five num1("3");
    Five num2("12");
    Five num3("203");
    EXPECT_THROW(num1 - num2, std::invalid_argument);
    EXPECT_THROW(num2 - num3, std::invalid_argument);
}

TEST(FiveClass, Comparison) {
    Five num1("12");
    Five num2("3");
    Five num3("12");
    
    EXPECT_TRUE(num1 > num2);
    EXPECT_TRUE(num2 < num1);
    EXPECT_TRUE(num1 == num3);
}

TEST(FiveClass, SizeConstructor) {
    Five num(5, '2');
    EXPECT_EQ(num.getSize(), 5);
    for(size_t i = 0; i < num.getSize(); ++i) {
        EXPECT_EQ(num.getDigit(i), '2');
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}