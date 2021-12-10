#include <iostream>
#include <memory>
#include <thread>
using namespace std;

class Foo{
public:
    Foo() = default;
    ~Foo(){
        cout << "~Foo" << endl;
    }
};

void func(const shared_ptr<Foo>& ptr, const string& str){
    cout << str << " " << ptr.use_count() << std::boolalpha << ptr.unique() << endl;
}

int main() {
    shared_ptr<Foo> ptr (new Foo);
    thread t1(func, ptr, "t1");
    thread t2(func, ptr, "t2");
    t1.join(); t2.join();
    cout << ptr.use_count() << std::boolalpha << ptr.unique() << endl;
    return 0;
}
