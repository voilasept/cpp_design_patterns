#include <string>
#include <iostream>
using namespace std;

struct Person
{
  int id {};
  string name {};
};

class PersonFactory
{
private:
    int global_id = 0;
public:
  Person create_person(const string& name)
  {
      auto new_person = Person {};
      new_person.id = global_id;
      new_person.name = name;
      global_id += 1;
      return new_person;
  }
};


int main(){
    auto pf = PersonFactory();
    auto p1 = pf.create_person("David");
    auto p2 = pf.create_person("Harry");
    cout << p1.id << p2.id << endl;
    return 0;
}