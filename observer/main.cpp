#include <iostream>
#include "node.h"
using namespace std;

int main() {
    MSG msgs [] = {
            {6001, 10, 2},
            {6002, 11, 5} };
    auto size = MsgSize {};
    auto price = MsgPrice {};
    auto sum_size_price = SumNodes {};
    auto mult_final = MultNodes {};
    cout << "sum_size_price hash: " << sum_size_price.get_seed() << endl;
    cout << "size hash: " << size.get_seed() << endl;
    cout << endl;

    size.subscribe(sum_size_price);
    cout << "sum_size_price hash: " << sum_size_price.get_seed() << endl;
    cout << "size hash: " << size.get_seed() << endl;
    cout << endl;

    price.subscribe(sum_size_price);
    sum_size_price.subscribe(mult_final);
    price.subscribe(mult_final);

    cout << "sum_size_price hash: " << sum_size_price.get_seed() << endl;
    cout << "size hash: " << size.get_seed() << endl;
    cout << endl;

    for(auto& msg : msgs) {
        cout << "updated: " << mult_final.notify(msg) << " ";
    }
    cout << endl;
    price.unsubscribe(mult_final);
    for(auto& msg : msgs) {
        cout << "updated: " << mult_final.notify(msg) << " ";
    }

    return 0;
}
