#ifndef MEDIATOR_CHATROOM_CHATROOM_H
#define MEDIATOR_CHATROOM_CHATROOM_H
#include <vector>
#include <cassert>
#include <stdexcept>
#include "person.h"
using namespace std;

class Person;

class ChatRoom{
private:
    vector<Person*> group {};
public:
    void add_person(Person* person);
    void broadcast(const string& msg, Person* origin);
};


#endif //MEDIATOR_CHATROOM_CHATROOM_H
