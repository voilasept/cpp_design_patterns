#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    int to_plus = 1;
    auto plus_one = [to_plus](const int x){
        return x+to_plus;
    };
    assert(plus_one(2) == 3);

    vector<int> inputs {1,2,3};
    transform(inputs.begin(), inputs.end(), inputs.begin(), plus_one);
    for (auto i:inputs) {
        cout << i << endl;
    }

    int a = 0;
    int b = 0;
    auto capture_by_value = [=](){
        // a+=1; b+=1; won't compile, as they are captured by value;
        return 0;
    };

    cout << capture_by_value() << endl;

    auto capture_by_ref = [&](){
        a += 1; b+=1;
        return a+b;
    };
    cout << capture_by_ref() << " " << a << " " << b << endl;

    auto capture_by_separate = [a, &b](){
        // a capture by value, b capture by ref
        return 0;
    };

    return 0;
}
