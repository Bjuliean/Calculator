#include <gtest/gtest.h>
#include <cctype>
#include "../controller/controller.h"

//DEFAULT
TEST(TestExpression, Test1) {
  s21::Controller a;
  std::string res = a.CountExpression("(5+4)/25.5*cos(5+2)^sin(3)+(255-55)^(ln(0.15)*√(123))+5^(sin(lg(4.6)))/asin(0.15)+acos(0.1)");
  EXPECT_DOUBLE_EQ(std::stod(res), 19.688589);
}

TEST(TestExpression, Test2) {
  s21::Controller a;
  std::string res = a.CountExpression("(5+3)*8-56+(3-3)*99/33");
  EXPECT_DOUBLE_EQ(std::stod(res), 8);
}

TEST(TestExpression, Test3) {
  s21::Controller a;
  std::string res = a.CountExpression("sin(783)*10000*(-1)/89-10+cos(12)");
  EXPECT_DOUBLE_EQ(std::stod(res), 66.890596);
}

TEST(TestExpression, Test4) {
  s21::Controller a;
  std::string res = a.CountExpression("sin(3.4+4.3)");
  EXPECT_DOUBLE_EQ(std::stod(res), 0.988168);
}

TEST(TestExpression, Test5) {
  s21::Controller a;
  std::string res = a.CountExpression("(4^acos(2/4)/tan(2*2)/5^acos(2/4)/tan(tan(tan(2*2))))");
  EXPECT_DOUBLE_EQ(std::stod(res), -0.589346);
}

TEST(TestExpression, Test6) {
  s21::Controller a;
  std::string res = a.CountExpression("1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1");
  EXPECT_DOUBLE_EQ(std::stod(res), 130);
}

TEST(TestExpression, Test7) {
  s21::Controller a;
  std::string res = a.CountExpression("  5 + 3 +  2 ");
  EXPECT_DOUBLE_EQ(std::stod(res), 10);
}

TEST(TestExpression, Test8) {
  s21::Controller a;
  std::string res = a.CountExpression("2(8+8)");
  EXPECT_DOUBLE_EQ(std::stod(res), 32);
}

TEST(TestExpression, Test9) {
  s21::Controller a;
  std::string res = a.CountExpression("2^3^2");
  EXPECT_DOUBLE_EQ(std::stod(res), 512);
}

TEST(TestExpression, Test10) {
  s21::Controller a;
  std::string res = a.CountExpression("5mod4");
  EXPECT_DOUBLE_EQ(std::stod(res), 1);
}

TEST(TestExpression, Test11) {
  s21::Controller a;
  std::string res = a.CountExpression("2,5+2,5");
  EXPECT_DOUBLE_EQ(std::stod(res), 5);
}


//WITH X
TEST(TestExpressionWithX, Test1) {
  s21::Controller a;
  std::string res = a.CountExpressionWithX("2x", 4);
  EXPECT_DOUBLE_EQ(std::stod(res), 8);
}

TEST(TestExpressionWithX, Test2) {
  s21::Controller a;
  std::string res = a.CountExpressionWithX("sin(cos(tan(-x)))", 4);
  EXPECT_DOUBLE_EQ(std::stod(res), 0.390649);
}

TEST(TestExpressionWithX, Test3) {
  s21::Controller a;
  std::string res = a.CountExpressionWithX("(-x)*(-x)", -4);
  EXPECT_DOUBLE_EQ(std::stod(res), 16);
}

TEST(TestExpressionWithX, Test4) {
  s21::Controller a;
  std::string res = a.CountExpressionWithX("-(-(-(-x*2)+2)+2)/2", -4);
  EXPECT_DOUBLE_EQ(std::stod(res), -4);
}


//UnoOperation
TEST(TestUno, Test1) {
  s21::Controller a;
  std::string res = a.UnoOperation("5");
  EXPECT_TRUE(res == "(-5");
}

TEST(TestUno, Test2) {
  s21::Controller a;
  std::string res = a.UnoOperation("-5");
  EXPECT_TRUE(res == "5");
}

TEST(TestUno, Test3) {
  s21::Controller a;
  std::string res = a.UnoOperation("-5+24");
  EXPECT_TRUE(res == "-5+(-24");
}

TEST(TestUno, Test4) {
  s21::Controller a;
  std::string res = a.UnoOperation("-5+24+(2+3)");
  EXPECT_TRUE(res == "-5+24+(2+3)*(-");
}

TEST(TestUno, Test5) {
  s21::Controller a;
  std::string res = a.UnoOperation("-5+24+(2+3)+(-5");
  EXPECT_TRUE(res == "-5+24+(2+3)+5");
}


//ERROR
TEST(TestError, Test1) {
  s21::Controller a;
  std::string res = a.CountExpression("(5+4)/25.5.*cos(5+2)^sin(3)+(255-55)");
  EXPECT_TRUE(res == "SYNTAX ERROR");
}

TEST(TestError, Test2) {
  s21::Controller a;
  std::string res = a.CountExpression("sin()*2");
  EXPECT_TRUE(res == "SYNTAX ERROR");
}

TEST(TestError, Test3) {
  s21::Controller a;
  std::string res = a.CountExpression("5+3-2+");
  EXPECT_TRUE(res == "SYNTAX ERROR");
}

TEST(TestError, Test4) {
  s21::Controller a;
  std::string res = a.CountExpression("8/(4-4)");
  EXPECT_TRUE(res == "DIV BY ZERO");
}

TEST(TestError, Test5) {
  s21::Controller a;
  std::string res = a.CountExpression("7^6+123*asd(354)");
  EXPECT_TRUE(res == "UNKNOWN ACTION: asd(");
}

TEST(TestError, Test6) {
  s21::Controller a;
  std::string res = a.CountExpressionWithX("cos(sin(123/(x-30+(-(10 + 10)))))", 50);
  EXPECT_TRUE(res == "DIV BY ZERO");
}

TEST(TestError, Test7) {
  s21::Controller a;
  std::string res = a.CountExpression("log(0.15)+.234.653");
  EXPECT_TRUE(res == "SYNTAX ERROR");
}

TEST(TestError, Test8) {
  s21::Controller a;
  std::string res = a.CountExpression("");
  EXPECT_TRUE(res == "");
}

TEST(TestError, Test9) {
  s21::Controller a;
  std::string res = a.CountExpression("PRIVETZDAROVA");
  EXPECT_TRUE(res == "UNKNOWN ACTION: PRIVETZDAROVA ");
}

TEST(TestError, Test10) {
  s21::Controller a;
  std::string res = a.CountExpression("tan(++4.12-)");
  EXPECT_TRUE(res == "SYNTAX ERROR");
}

TEST(TestError, Test11) {
  s21::Controller a;
  std::string res = a.CountExpression("5mod(5-5)");
  EXPECT_TRUE(res == "DIV BY ZERO");
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}