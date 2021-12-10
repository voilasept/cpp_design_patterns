#include <iostream>
#include "drinks.h"
using namespace std;

int main() {
    auto drink = TeaFactory().make();
    auto drink2 = CoffeeFactory().make();
    cout << "-------" << endl;
    auto drinkMap = DrinkMap();
    auto drink3 = drinkMap.makeDrink("Coffee");
    auto drink4 = drinkMap.makeDrink("Tea");
    cout << "-------" << endl;
    auto fmap = FunctorMap();
    auto drink5 = fmap.make_drink("Coffee", 88);
    auto drink6 = fmap.make_drink("Tea", 66);
    return 0;
}
