#include <iostream>
#include <vector>
using namespace std;

// forward declaration
template<typename T, typename ... Args>
T my_sum(Args&& ...);

template<typename T>
class ForwardExample{
private:
    T summed;
public:
    template<typename ... Args>                 // template parameter pack
    explicit ForwardExample(Args&& ... args);   // function parameter pack
};

template<typename T>
template<typename... Args>
ForwardExample<T>::ForwardExample(Args &&... args) {
    summed = my_sum<T>(std::forward<Args>(args)...);   // variadic forwarding
    // https://stackoverflow.com/questions/2821223/how-would-one-call-stdforward-on-all-arguments-in-a-variadic-function
    cout << "Instantiated " << summed << endl;
}

template<typename T, typename ... Args>
T my_sum(Args&& ... args){
    vector<T> vargs {args...};
    T total_val {};
    for(auto x : vargs){
        total_val += x;
    }
    return total_val;
}

int main() {
    ForwardExample<int>(3, 2, 4);
    return 0;
}
