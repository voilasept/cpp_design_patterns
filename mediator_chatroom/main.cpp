#include "person.h"
#include "chatroom.h"
using namespace std;

int main() {
    ChatRoom chatroom {};
    Person Aziz {"Aziz"};
    Person David {"David"};
    Person Zeh {"Zeh"};

    chatroom.add_person(&Aziz);
    chatroom.add_person(&David);
    Aziz.broadcast("Hello guys");

    chatroom.add_person(&Zeh);
    David.broadcast("Bye all");

    return 0;
}
