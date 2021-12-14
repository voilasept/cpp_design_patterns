#include "person.h"

void Person::broadcast(const string &msg){
    chatroom->broadcast(msg, this);
}

void Person::receive(const string &msg) const {
    cout << name << " receives : " << msg << endl;
}
