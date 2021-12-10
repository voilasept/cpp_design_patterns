#include <iostream>
#include <vector>
using namespace std;

/*
 * This is the modern way: variadic template function
 */
template<typename T, typename ... Args> // template parameter pack
T my_print(const Args& ... args){       // function parameter pack
    vector<T> vint {args...};           // pack expansion
    T summed = 0;
    for (auto vi : vint){
        summed += vi;
    }
    return summed;
}


int main() {
    cout << my_print<int>(1, 2, 3) << endl;
    cout << my_print<double>(1.2, 2.3) << endl;
    cout << my_print<int>() << endl;
    return 0;
}
