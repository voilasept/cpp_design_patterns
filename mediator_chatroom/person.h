#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

#ifndef MEDIATOR_CHATROOM_PERSON_H
#define MEDIATOR_CHATROOM_PERSON_H
#include <iostream>
#include <string>
#include <utility>
#include "chatroom.h"
using namespace std;

class ChatRoom;

class Person{
public:
    ChatRoom* chatroom;
    string name;
    Person(string name):name(move(name)){}
    bool operator==(const Person& other) const {
        return name == other.name;
    }
    bool operator!=(const Person& other) const {
        return not (*this==other);
    }
    void broadcast(const string& msg);
    void receive(const string& msg) const;
};

#endif //MEDIATOR_CHATROOM_PERSON_H

#pragma clang diagnostic pop