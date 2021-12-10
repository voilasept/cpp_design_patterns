#include <iostream>
#include "car.h"
#include "car_factory.h"

int main() {
    CheapCar car = CheapCar();
    car.makeBody();

    LuxuryCar car2 = LuxuryCar();
    car2.makeBody();

    auto factory = CheapCarFactory();
    auto car3 = factory.buildCar();
    auto car4 = factory.buildCar();
    auto car5 ( LuxuryCarFactory().buildCar() );

    car3->describe();
    car4->describe();
    car5->describe();

    return 0;
}
