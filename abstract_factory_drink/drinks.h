#ifndef ABSTRACT_FACTORY_DRINK_DRINKS_H
#define ABSTRACT_FACTORY_DRINK_DRINKS_H

#include <memory>
#include <iostream>
#include <map>
#include <cassert>
#include <functional>
using namespace std;

class Drink{
public:
    virtual ~Drink() {
        cout << "Drink Destroyed" << endl;
    }
    virtual void prepare(int volume) const = 0;
};

class Coffee final : public Drink{
public:
    ~Coffee() override{
        cout << "Destroyed Coffee!" << endl;
    }
    void prepare(int volume) const override{
        cout << "Coffee " << volume << " " <<
        this << endl;
    }
};

class Tea final : public Drink{
public:
    ~Tea() override{
        cout << "Destroyed Tea!" << endl;
    }
    void prepare(int volume) const override{
        cout << "Coffee" << volume << " " <<
        this << endl;
    }
};


class DrinkFactory{
public:
    virtual ~DrinkFactory() = default;
    virtual unique_ptr<Drink> make() = 0;
};

class CoffeeFactory : public DrinkFactory{
public:
    unique_ptr<Drink> make() override{
        unique_ptr<Coffee> coffee = make_unique<Coffee>();
        coffee->prepare(10);
        return coffee;
    }
};

class TeaFactory : public DrinkFactory{
public:
    unique_ptr<Drink> make() override{
        unique_ptr<Tea> tea = make_unique<Tea>();
        tea->prepare(20);
        return tea;
    }
};


class DrinkMap{
public:
    map<string, unique_ptr<DrinkFactory>> drinkMap;
    DrinkMap(){
        drinkMap["Coffee"] = make_unique<CoffeeFactory>(CoffeeFactory());
        drinkMap["Tea"] = make_unique<TeaFactory>(TeaFactory());
    }
    unique_ptr<Drink> makeDrink(const string& drink_name){
        assert(drinkMap.find(drink_name) != drinkMap.end());
        return drinkMap[drink_name]->make();
    }
};

class FunctorMap{
private:
    map< string, function< unique_ptr<Drink>(int) > > functor_map;
public:
    FunctorMap(){
        functor_map["Coffee"] = [](int volume){
            auto coffee = make_unique<Coffee>();
            coffee->prepare(volume);
            return coffee;
        };
        functor_map["Tea"] = [](int volume){
            auto tea = make_unique<Tea>();
            tea->prepare(volume);
            return tea;
        };
    }
    unique_ptr<Drink> make_drink(const string& drink_name, int volume){
        assert(functor_map.find(drink_name) != functor_map.end());
        return functor_map[drink_name](volume);
    }
};

#endif //ABSTRACT_FACTORY_DRINK_DRINKS_H
