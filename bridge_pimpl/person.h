#ifndef BRIDGE_PIMPL_PERSON_H
#define BRIDGE_PIMPL_PERSON_H
#include <string>
using namespace std;

class Person{
private:
    string name;
public:
    explicit Person(string name);
    ~Person();
    void greet();
    class PersonImpl;
};

#endif //BRIDGE_PIMPL_PERSON_H
