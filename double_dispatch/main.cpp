#include <iostream>
#include "expression.h"
#include "visitor.h"
using namespace std;

int main() {
    auto* exp_left = new AdditionExpression(
            new DoubleExpression {1},
            new DoubleExpression {2});
    auto* exp_right = new DoubleExpression {3};
    auto exp = AdditionExpression(exp_left, exp_right);

    auto visitor = Visitor {};
    visitor.visit(&exp);
    cout << visitor.oss.str() << endl;
    return 0;
}
