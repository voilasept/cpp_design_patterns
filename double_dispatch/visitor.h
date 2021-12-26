#ifndef DOUBLE_DISPATCH_VISITOR_H
#define DOUBLE_DISPATCH_VISITOR_H
#include <sstream>
#include "expression.h"
using namespace std;

class DoubleExpression;
class AdditionExpression;

class Visitor{
public:
    ostringstream oss {""};
    void visit(DoubleExpression* de);
    void visit(AdditionExpression* ae);
};

#endif //DOUBLE_DISPATCH_VISITOR_H
