#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <memory>
#include <ctime>
#include <string>
using namespace std;

void hello(mutex& mtx){
    mtx.lock();
    cout << "Inside: " << this_thread::get_id() << " " << clock() << endl;
    mtx.unlock();
}

void risky_increment(int& value){
    if( clock() % 10000 == 0){
        throw exception();
    }
    value++;
}

/*
 * The scoped_lock is a strictly superior version of lock_guard
 * that locks an arbitrary number of mutexes all at once
 * (using the same deadlock-avoidance algorithm as std::lock).
 * In C++>=17, you should only ever use scoped_lock.
 * e.g. std::scoped_lock<std::mutex, std::mutex> lock(mtx1, mtx2);
 */
typedef scoped_lock<recursive_mutex> ScopedLock;

class Counter{
private:
    // can't use std::mutex otherwise increment_twice->increment becomes deadlock
    std::recursive_mutex mtx;
    int value;
public:
    Counter():value(0), mtx(){}
    void increment(){
        // lock_guard is like smart ptr, get destroyed out-of-scope and release mtx
        ScopedLock guard(mtx);
        risky_increment(value);
    }
    void increment_twice(){
        ScopedLock guard(mtx);
        increment();
        increment();
    }
    int get_value() const { return value; }
};


int main() {
    mutex mtx {};
    vector<unique_ptr<thread>> threads {};
    threads.reserve(4);
    for(int i=0; i<4; i++) {
        threads.emplace_back( make_unique<thread>( [&]() { hello(mtx); } ) );
    }
    for(auto& t : threads){
        mtx.lock();
        cout << "Spawned: " << t->get_id() << " " << clock() << endl;
        mtx.unlock();
    }
    for(auto& t:threads) {
        t->join();
    }

    Counter counter {};
    thread t1([&](){ for (int i=0; i<1000; i++) counter.increment_twice(); });
    thread t2([&](){ for (int i=0; i<1000; i++) counter.increment(); });
    thread t3([&](){ for (int i=0; i<1000; i++) counter.increment(); });

    t1.join();
    t2.join();
    t3.join();
    cout << "Final: " << counter.get_value() << endl;

    return 0;
}
