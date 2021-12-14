#include "chatroom.h"

void ChatRoom::add_person(Person* person) {
    auto found = find_if(
            group.begin(), group.end(),
            [&](auto p){return *person==*p;} );
    if(found != group.end()){
        throw std::invalid_argument("repeated"s + person->name);
    }
    group.push_back(person);
    string msg = person->name + " joins the chat\n";
    person->chatroom = this;
    broadcast(msg, nullptr);
}

void ChatRoom::broadcast(const string &msg, Person *origin) {
    for(auto p : group){
        if (not origin){
            p->receive(msg);
        }
        else if(*p != *origin){
            p->receive(origin->name + " : "s + msg);
        }
    }
}