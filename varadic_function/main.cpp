#include <iostream>
#include <cstdarg>  // include this
#include <sstream>
#include <cassert>
using namespace std;

/*  This is the old way from C.
    NO information about the number/type of variadic arguments are automatically passed!
    Restrictions:
    1. argument list NO promotable type (aka NO signed int, char [promote to int], NO float [promote to double])
    2. rightmost argument can't be reference type, aka NO int& n_param. Instead, pass by pointer!
    3. va_arg arguments must be plain type, can't be non-trivial objects (struct/class).
*/
ostringstream format_string(char* fmt, int n_param, ...){    // pure variadic args (...) is not allowed
    ostringstream os;
    va_list args;
    va_start(args, n_param);    // 2nd argument is the last normal arg preceding variadic arguments...
    while(*fmt != '\0'){
        if (*fmt == 'c'){
            auto var = static_cast<char>(va_arg(args, int));
            os << var << " ";
        }
        else if (*fmt == 'd'){
            auto var = va_arg(args, double);
            os << var << " ";
        }
        else if (*fmt == 'i'){
            auto var = va_arg(args, int);
            os << var << " ";
        }
        else{
            throw std::invalid_argument("invalid");
        }
        fmt++;
        n_param--;
    }
    assert(n_param == 0);
    va_end(args);
    return os;
}


int main() {
    string format {"cdi"};
    auto os = format_string(&format[0],3, 'x', 3.14, 5);
    cout << os.str() << endl;
    return 0;
}
