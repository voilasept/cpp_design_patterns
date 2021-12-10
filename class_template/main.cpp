#include <iostream>
using namespace std;

template <typename AddType>
class Adder{
public:
    Adder() = default;
    AddType x;
    explicit Adder(AddType x): x(x){}
    AddType add_one(){return x+1;}
};

int main() {
    auto a1 = Adder<int>(1);
    cout << a1.add_one() << endl;
    auto a2 = Adder<float>(1.1);
    cout << a2.add_one() << endl;
    return 0;
}
