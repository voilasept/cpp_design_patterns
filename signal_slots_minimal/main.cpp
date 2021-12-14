#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
#include <iostream>
#include <vector>
#include <boost/signals2.hpp>
#include <numeric>
using namespace std;

void hello(){
    cout << "hello" << endl;
}

template<typename T>
void hello_vec(vector<T> vec, int n){
    for(const auto& x : vec){ cout << x << " "; }
    cout << endl << n << endl;
}

class Task {
public:
    string name;
    Task(string name):name(move(name)){}
    void work() const {
        cout << "work on " << name << endl;
    }
};

template<typename T>    // T: return type of combiner
class ReturnAll{
public:
    typedef T result_type;  // mandatory, result_type is a keyword in boost::signals2
    ReturnAll() = default;     // combiner ctor can't have any argument
    template<typename InputIterator>
    T operator()(InputIterator begin, InputIterator end) const {
        return T {begin, end};  // std::vector(InputIterator first, InputIterator last)
    }
};

template<typename T>
class ReturnSum{
public:
    typedef T result_type;
    ReturnSum() = default;
    template<typename InputIterator>
    T operator()(InputIterator begin, InputIterator end) const {
        return std::accumulate(begin, end, 0);
    }
};


int main() {
    // example 1:
    cout << "Example 1" << endl;
    boost::signals2::signal<void()> sig;
    //                      ~~~~~~ signature of event-handler function
    sig.connect(hello);
    sig();
    sig.disconnect(hello);
    sig();
    cout << "disconnected, no op" << endl;
    cout << endl;


    // example 2:
    cout << "Example 2" << endl;
    boost::signals2::signal<void(vector<int>, int)> sig_vec;
    sig_vec.connect(hello_vec<int>);
    sig_vec({3,1,4}, 5);
    cout << endl;

    // example 3: signal -> signal -> slot
    cout << "Example 3" << endl;
    boost::signals2::signal<void()> sig2, sig3;
    sig2.connect(sig3);
    sig3.connect(hello);
    sig2();
    cout << endl;

    // example 4:
    cout << "Example 4" << endl;
    boost::signals2::signal<void()> sig4;
    Task t0 {"Job0"}, t1 {"Job1"};
    sig4.connect([task_ptr = &t0] { task_ptr->work(); },
                 boost::signals2::connect_position::at_front);
    sig4.connect([&](){ t1.work(); },
                 boost::signals2::connect_position::at_front);
    sig4();
    cout << "num of slots: " << sig4.num_slots() << boolalpha << " Empty? " <<sig4.empty() << endl;
    sig4.disconnect_all_slots();

    // example 5:
    cout << "Example 5" << endl;
    boost::signals2::signal<int(int)> sig5;
    sig5.connect([](int x){ return x * 2; });
    sig5.connect([](int x) { return x * 3; });
    boost::optional<int> result = sig5(2);  // by default, ignore all return values except the last of the chain
    cout << *result << endl;    // must be de-referenced to get int

    //example 6: Combiner (return vector)
    cout << "Example 6" << endl;
    boost::signals2::signal<int(int), ReturnAll<vector<int>>> sig6;
    //                                          ~~~~~~
    // only vector allowed as it admits InputIterator ctor, array is not allowed!
    sig6.connect([](int x){ return x * 2; });
    sig6.connect([](int x) { return x * 3; });
    vector<int> result2 = sig6(2);
    for(auto x : result2){
        cout << x << " ";
    }
    cout << endl;

    // example 7: Combiner (return scalar)
    cout << "Example 7" << endl;
    boost::signals2::signal<int(int), ReturnSum<int>> sig7;
    sig7.connect([](int x){ return x * 2; });
    sig7.connect([](int x) { return x * 3; });
    int x = sig7(2);
    cout << x << endl;

    return 0;
}
