#ifndef MULTITON_MULTITON_H
#define MULTITON_MULTITON_H

#include <memory>
using namespace std;

template<typename Type, typename Key>
class Multiton{
private:
    static map<Key, shared_ptr<Type>> instances;
public:
    Multiton<Type, Key>() = delete;
    ~Multiton<Type, Key>() = delete;
    Multiton<Type, Key>(const Multiton&) = delete;
    Multiton<Type, Key>& operator=(const Multiton<Type, Key>&) = delete;

    static shared_ptr<Type> get(const Key& key){
        // ;-separated local variable ins (since C++17)
        if(const auto ins = instances.find(key); ins != instances.end()){
            return ins->second;
        }
        instances[key] = shared_ptr<Type>(new Type);
        return instances[key];
    }
};

template<typename Type, typename Key>
map<Key, shared_ptr<Type>> Multiton<Type, Key>::instances {};

#endif //MULTITON_MULTITON_H
