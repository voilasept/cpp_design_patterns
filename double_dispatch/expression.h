#ifndef DOUBLE_DISPATCH_EXPRESSION_H
#define DOUBLE_DISPATCH_EXPRESSION_H

#include "visitor.h"

class Visitor;

class Expression{
public:
    virtual ~Expression() = default;
    /* the core idea is the "visit-accept double hop",
     * the goal is to create static binding in a non-intrusive way.
    */
    virtual void accept(Visitor* visitor) = 0;
};

class DoubleExpression : public Expression{
public:
    double value;
    explicit DoubleExpression(double value);
    void accept(Visitor* visitor);
};

class AdditionExpression : public Expression{
public:
    Expression* left;
    Expression* right;
    AdditionExpression(Expression* left, Expression* right);
    void accept(Visitor* visitor);
};

#endif //DOUBLE_DISPATCH_EXPRESSION_H
