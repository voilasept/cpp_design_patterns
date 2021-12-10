#include <iostream>
#include <vector>
using namespace std;

class Order{    // Order is the "bridge".
public:
    explicit Order(int price) : price(price){}
    virtual ~Order() = default;
    virtual void send_order() = 0;
    int price;
};

class LimitOrder : public Order{
public:
    explicit LimitOrder(int price) : Order(price) {}
    void send_order() override{
        cout << "LimitOrder sent @" << price << endl;
    }
};

class MarketOrder : public Order{
public:
    explicit MarketOrder(int price) : Order(price) {}
    void send_order() override{
        cout << "MarketOrder sent @" << price << endl;
    }
};

class Trader{
public:
    vector<Order*> orders;
    Trader() = default;
    void register_order(Order* optr){
        orders.emplace_back(optr);
    }
    void send_batch_orders(){
        for(auto o : orders){
            o->send_order();
        }
    }
};

int main() {
    auto* lo = new LimitOrder(12);
    auto* mo = new MarketOrder(15);
    Trader trader {};
    trader.register_order(lo);
    trader.register_order(mo);
    trader.send_batch_orders();
    return 0;
}
