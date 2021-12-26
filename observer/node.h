#ifndef OBSERVER_NODE_H
#define OBSERVER_NODE_H

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <mutex>
#include <boost/functional/hash.hpp>
using namespace std;

struct MSG{
    long int sequence;
    double price;
    double size;
    MSG(long sequence, double price, double size)
            :sequence(sequence), price(price), size(size){}
};

// optional thread safety
typedef scoped_lock<recursive_mutex> ScopedLock;

class Node{
protected:
    vector<Node*> observers;
    vector<Node*> deps;
    recursive_mutex mtx;
    size_t seed;
public:
    double value;
    long int last_sequence = -1;
    Node() {seed = 0x11111111; value = 0;}
    void subscribe(Node& observer) {
        ScopedLock lock {mtx};
        assert(find(observers.begin(), observers.end(), &observer) == observers.end());
        observers.push_back(&observer);
        observer.deps.push_back(this);
        boost::hash_combine(observer.seed, seed);
    }
    void unsubscribe(Node& observer) {
        ScopedLock lock {mtx};
        observers.erase(
                remove(observers.begin(), observers.end(), &observer),
                observers.end()
        );
        observer.deps.erase(
                remove(observer.deps.begin(), observer.deps.end(), this),
                observer.deps.end()
        );
    }
    void prepare_deps(MSG& msg){
        ScopedLock lock {mtx};
        if (last_sequence != msg.sequence) {
            for (auto &dep: deps) {
                dep->notify(msg);
            }
            last_sequence = msg.sequence;
        }
    }
    virtual double notify(MSG& msg) = 0;
    [[nodiscard]] size_t get_seed() const {
        return seed;
    }
};


class MsgSize : public Node{
public:
    double notify(MSG& msg) override{
        value = msg.size;
        return value;
    }
    MsgSize(){
        boost::hash_combine(seed, "MsgSize");
    }
};

class MsgPrice : public Node{
public:
    double notify(MSG& msg) override{
        value = msg.price;
        return value;
    }
    MsgPrice(){
        boost::hash_combine(seed, "MsgPrice");
    }
};

class SumNodes : public Node{
public:
    double notify(MSG& msg) override{
        prepare_deps(msg);
        value = 0;
        for(auto& dep : deps){
            value += dep->value;
        }
        return value;
    }
    SumNodes(){
        boost::hash_combine(seed, "SumNodes");
    }
};

class MultNodes : public Node{
public:
    double notify(MSG& msg) override{
        prepare_deps(msg);
        value = 1;
        for(auto& dep : deps){
            value *= dep->value;
        }
        return value;
    }
    MultNodes(){
        boost::hash_combine(seed, "MultNodes");
    }
};

#endif //OBSERVER_NODE_H
