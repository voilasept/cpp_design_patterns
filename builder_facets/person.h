#pragma once

#include <string>
#include <utility>

class PersonBuilder;

class Person{
    friend class PersonBuilder;
private:
    std::string street_address, post_code, city;
    std::string company_name, position;
    int annual_income {0};
    Person() = default;
public:
    static PersonBuilder create();

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};

class PersonBuilder{
private:
    Person p;
public:
    PersonBuilder() = default;
    PersonBuilder& works(std::string position){
        p.position = std::move(position);
        return *this;
    }
    PersonBuilder& lives(std::string city){
        p.city = std::move(city);
        return *this;
    }
    operator Person(){
        return std::move(p);
    }
};

PersonBuilder Person::create() {
    return {};
}
