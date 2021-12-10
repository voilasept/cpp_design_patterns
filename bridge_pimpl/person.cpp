#include <iostream>
#include "person.h"

class Person::PersonImpl{
public:
    PersonImpl() = default;
    ~PersonImpl() = default;

    // in the class greet is non-static, but better to be static
    // and no need to instantiate PersonImpl.
    static void greet(Person* person){
        std::cout << "Hello " << person->name << std::endl;
    }
};

Person::Person(string name): name(std::move(name)){}
Person::~Person() = default;

void Person::greet(){
    PersonImpl::greet(this);
}
