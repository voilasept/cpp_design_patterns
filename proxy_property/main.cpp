#include <iostream>
using namespace std;

/*
 * Property behaves the same as int.
 */
template<typename T>
class Property{
private:
    T value;
    T old_value;
public:
    Property(T&& value):value(value), old_value(value){}
    Property(const Property& other){
        value = other.value;
        old_value = other.old_value;
    }
    Property& operator=(const Property& other){
        old_value = value;
        value = other.value;
        return *this;
    }
    operator T(){return value;}
    T last() const {
        return old_value;
    }
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
    cout << q.height << " " << q.height.last() << endl;
    Property<int> z {130};
    cout << z << endl;
    return 0;
}
