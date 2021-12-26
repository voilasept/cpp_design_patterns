#include "expression.h"

DoubleExpression::DoubleExpression(double value):value(value) {}

AdditionExpression::AdditionExpression(Expression *left, Expression *right)
        :left(left), right(right) {}


void DoubleExpression::accept(Visitor *visitor) {
    /* "this" allows static binding.
     * This solves the problem of using
     * if (dynamic_cast<DoubleExpression>(expression_ptr))
     * which creates run_time overhead.
     */
    visitor->visit(this);
}

void AdditionExpression::accept(Visitor *visitor) {
    visitor->visit(this);
}


