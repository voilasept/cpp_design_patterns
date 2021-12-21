#ifndef OBSERVER_NODE_H
#define OBSERVER_NODE_H

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

struct MSG{
    long int sequence;
    double price;
    double size;
    MSG(long sequence, double price, double size)
            :sequence(sequence), price(price), size(size){}
};


class Node{
public:
    vector<Node*> observers;
    vector<Node*> deps;
    double value;
    long int last_sequence = -1;
    void subscribe(Node& observer) {
        assert(find(observers.begin(), observers.end(), &observer) == observers.end());
        observers.push_back(&observer);
        observer.deps.push_back(this);
    }
    void unsubscribe(Node& observer) {
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
        if (last_sequence != msg.sequence) {
            for (auto &dep: deps) {
                dep->notify(msg);
            }
            last_sequence = msg.sequence;
        }
    }
    virtual double notify(MSG& msg) = 0;
};


class MsgSize : public Node{
public:
    double notify(MSG& msg) override{
        value = msg.size;
        return value;
    }
};

class MsgPrice : public Node{
public:
    double notify(MSG& msg) override{
        value = msg.price;
        return value;
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
};

#endif //OBSERVER_NODE_H
