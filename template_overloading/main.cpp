#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Person{
private:
    string name;
public:
    void set_name();
    string get_name() const;
};

template<>
void Person<int>::set_name() {
    name = "is int";
}

template<typename T>
void Person<T>::set_name() {
    name = "not int";
}

template<typename T>
string Person<T>::get_name() const {
    cout << name << endl;
    return name;
}

int main() {
    Person<int> p0;
    p0.set_name();
    p0.get_name();

    Person<float> p1;
    p1.set_name();
    p1.get_name();
    return 0;
}
