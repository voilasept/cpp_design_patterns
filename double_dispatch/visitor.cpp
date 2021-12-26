#include <iostream>
#include "visitor.h"
using namespace std;

// actual logic done in (external) visitor

void Visitor::visit(DoubleExpression *exp) {
    oss << exp->value;
}

void Visitor::visit(AdditionExpression *exp) {
    oss << "(";
    exp->left->accept(this);
    oss << "+";
    exp->right->accept(this);
    oss << ")";
}

