#ifndef ABSTRACT_FACTORY_CAR_CAR_FACTORY_H
#define ABSTRACT_FACTORY_CAR_CAR_FACTORY_H

#include "car.h"
#include <memory>
using namespace std;

class CarFactory{
public:
    /*
    if Car doesn't define a virtual destructor, line 19's poloymorphism
    will send error message at car destructor, because only base destructor
    [~Car] would be called, not derived destructor [~CheapCar]
     */
    unique_ptr<Car> car;
    virtual unique_ptr<Car> && buildCar() = 0;
    virtual ~CarFactory() = default; // that's a good habit!
};

class CheapCarFactory : public CarFactory{
public:
    unique_ptr<Car> && buildCar() override{
        car = make_unique<CheapCar>();
        car->makeBody();
        return move(car);
    }
};

class LuxuryCarFactory : public CarFactory{
public:
    unique_ptr<Car> && buildCar() override {
        car = make_unique<LuxuryCar>();
        car->makeBody();
        return move(car);
    }
};

#endif //ABSTRACT_FACTORY_CAR_CAR_FACTORY_H
