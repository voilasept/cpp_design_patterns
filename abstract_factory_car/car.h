#ifndef ABSTRACT_FACTORY_CAR_CAR_H
#define ABSTRACT_FACTORY_CAR_CAR_H
#include <memory>
#include <string>
#include <iostream>
using namespace std;

class Body{
public:
    int strength {};
    explicit Body(int strength) : strength(strength) {
        cout << "Strengh " << strength << "Body Made!" << endl;
    }
    void describe() const {
        cout << "Described " << strength << endl;
    }
};

class CheapBody : public Body{
public:
    CheapBody():Body(50){}
};

class LuxuryBody: public Body{
public:
    LuxuryBody():Body(100){}
};

class Car{
public:
    string name {};
    unique_ptr<Body> body;
    virtual void makeBody() = 0;
    virtual ~Car() = default;   // important
    void describe() const {
        body->describe();
    }
};

class CheapCar : public Car{
public:
    void makeBody() override{
        body = make_unique<CheapBody>();
    }
};

class LuxuryCar : public Car{
public:
    void makeBody() override{
        body = make_unique<LuxuryBody>();
    }
};

#endif //ABSTRACT_FACTORY_CAR_CAR_H
