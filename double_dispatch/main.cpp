#include <iostream>
#include "expression.h"
#include "visitor.h"
using namespace std;

#include "gtest/gtest.h"


TEST(double_dispatch, test1) {
    cout << "Running TEST 1" << endl;
    auto* exp_left = new AdditionExpression(
            new DoubleExpression {1},
            new DoubleExpression {2});
    auto* exp_right = new DoubleExpression {3};
    auto exp = AdditionExpression(exp_left, exp_right);

    auto visitor = Visitor {};
    visitor.visit(&exp);
    cout << visitor.oss.str() << endl;
    EXPECT_EQ("((1+2)+3)", visitor.oss.str());
}


TEST(double_dispatch, test2){
    cout << "Running TEST 2" << endl;
    EXPECT_EQ(10*100, 1000);
}