#include <iostream>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
using namespace std;

struct Fibo;
typedef boost::flyweight<boost::flyweights::key_value<int, Fibo>> MemoizeFibo;

/*
 * Avoid boost::flyweight! Use manual flyweight instead.
 */

struct Fibo{
    explicit Fibo(int n){
        if(n==0 or n==1){
            value = 1;
        }
        else{
            value = MemoizeFibo(n - 1).get().value + MemoizeFibo(n - 2).get().value;
        }
    }
    int value;
};

typedef boost::flyweight<string> MemoizeString;

int main() {
    // key_value memoize
    cout << MemoizeFibo(5).get().value << endl;
    // key memoize
    MemoizeString s1 {"Hello"};
    MemoizeString s2 {"Hello"};
    MemoizeString s3 {"World"};
    cout << &s1.get() << " " << &s2.get() << " " << &s3.get() <<endl;
    return 0;
}
