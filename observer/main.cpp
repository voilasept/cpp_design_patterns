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

    size.subscribe(sum_size_price);
    price.subscribe(sum_size_price);
    sum_size_price.subscribe(mult_final);
    price.subscribe(mult_final);

    for(auto& msg : msgs) {
        cout << "updated: " << mult_final.notify(msg) << " ";
    }
    return 0;
}
