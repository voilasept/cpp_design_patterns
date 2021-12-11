#include <iostream>
#include <string>
#include <boost/bimap.hpp>
using namespace std;

typedef uint16_t KEY;
typedef boost::bimap<KEY, string> BMAP;

class NameStore{
private:
    NameStore() = default;
    KEY next_key;
    BMAP* name_map;
    static NameStore* self;
public:
    KEY get_next_key(){
        return next_key++;
    }
    BMAP* operator()(){
        return name_map;
    }
    static NameStore* get();
    void print() const;
};

NameStore* NameStore::self {nullptr};
NameStore* NameStore::get(){
    if (self == nullptr){
        self = new NameStore {};
        self->name_map = new BMAP {};
    }
    return self;
}

void NameStore::print() const{
    for(auto iter=name_map->begin(); iter!=name_map->end(); iter++){
        cout << iter->left << " : " << iter->right << endl;
    }
}

class Name{
private:
    KEY first_key, last_key;
public:
    Name(const string& first_str, const string& last_str, NameStore& store):
            first_key(add(first_str, store)), last_key(add(last_str, store)) {}
    KEY add(const string& name_str, NameStore& store){
        KEY target_key;
        if (auto first_key_iter = store()->right.find(name_str);
                first_key_iter != store()->right.end()) {
            target_key = first_key_iter->second;
        } else {
            target_key = store.get_next_key();
            // store()->insert(BMAP::value_type(target_key, name_str));
            store()->insert({target_key, name_str});    // this is better
        }
        return target_key;
    }
    [[nodiscard]] string to_name(NameStore& store) const{
        ostringstream oss;
        oss << store()->left.at(first_key) << "@" << first_key << " "
            << store()->left.at(last_key) << "@" << last_key << endl;
        return oss.str();
    }
};


int main() {
    auto* store = NameStore::get();
    auto john1 = Name("John", "Nash", *store);
    auto john2 = Name("John", "Wang", *store);
    cout << john1.to_name(*store) << endl;
    cout << john2.to_name(*store) << endl;
    store->print();
    return 0;
}
