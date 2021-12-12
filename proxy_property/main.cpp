#include <iostream>
using namespace std;

/*
 * Property behaves the same as int.
 */
template<typename T>
class Property{
public:
    T value;
    Property(T&& value):value(value){}
    Property(const Property& other){value = other.value;}
    Property& operator=(const Property& other){value = other.value; return *this;}
    operator T(){return value;}
};

class Person{
public:
    Property<int> height {178};
    Property<int> weight {150};
};

int main() {
    Person p {};
    int height = p.height;
    int sum = p.height + p.weight + 30;
    cout << height << " " << sum << endl;
    Person q {p};
    cout << q.height << " " << q.weight << endl;
    q.height = 20;
    cout << q.height << endl;
    Property<int> z {130};
    cout << z << endl;
    return 0;
}
