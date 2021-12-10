#include <iostream>
#include "person.h"
using namespace std;

int main() {
    auto person = Person("Han");
    person.greet();
    return 0;
}
