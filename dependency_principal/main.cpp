#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <string>
using namespace std;

enum class Relation{
    parent,
    child,
    sibling
};

class Person {
public:
    string name;
    bool _eq_(const Person & other) const{
        //    const: other can't be changed
        //                          const: this func can't modify member variables
        return name == other.name;
    }
};

struct RelationshipBrowser{
public:
    virtual vector<Person> find_children_of (Person & person) = 0;
    virtual void print() = 0;
};

class Relationships : public RelationshipBrowser{
private:
    vector<tuple<Person, Relation, Person>> relations;
public:
    void add_parent_and_child(const Person & parent, const Person & child){
        relations.emplace_back(parent, Relation::parent, child);
        relations.emplace_back(child, Relation::child, parent);
    }
    vector<Person> find_children_of (Person & person) override {
        vector<Person> children;    // memory is in stack, gets released after out-of-scope
        for(auto && [p1, rel, p2] : relations){
            if(person._eq_(p1) and rel==Relation::parent){
                cout << "John is the parent of " << p2.name << endl;
                children.push_back(p2);
            }
        }
        return children;
    }

    void print() override{
        for(auto && [p1, rel, p2] : relations){
            cout << p2.name << endl;
        }
    }
};

class Research{
public:
    explicit Research(RelationshipBrowser & relationships){
        // Research depend on base class [RelationshipBroswer]
        Person john {"John"};
        auto children = relationships.find_children_of(john);
        cout << "Children of John: ";
        for (auto & child : children){
            cout << child.name << " ";
        }
        cout << endl;
    }
};

int main() {
    Person john {"John"};
    Person chris {"Chris"};
    Person matt {"Matt"};
    Relationships rels;
    rels.add_parent_and_child(john, chris);
    rels.add_parent_and_child(john, matt);
    rels.print();
    Research _ {rels};
    rels.print();

    ostringstream oss;  // output string stream
    oss << 1.2 << endl;
    string oss_str = oss.str();
    cout << oss_str << endl;

    string words [] = {"A", "B"};
    for(auto & w : words){
        w[0] = 'C';
    }
    cout << words[0] << endl;
    return 0;
}
