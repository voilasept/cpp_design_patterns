#include <iostream>
#include <vector>
#include <boost/signals2.hpp>
using namespace std;

struct IParticipant{
    int value {};
    virtual void say(int value) = 0;
};

struct Mediator{
    vector<IParticipant*> participants {};
    boost::signals2::signal<void(int, IParticipant*)> notify {};
};

struct Participant : IParticipant
{
    Mediator& mediator;

    explicit Participant(Mediator &mediator) : mediator(mediator)
    {
        mediator.participants.push_back(this);
        mediator.notify.connect(
                [&](int value, IParticipant* p){
                    if (p!=this){
                        this->value += value;
                    }
                }
        );
    }

    void say(int value) override {
        mediator.notify(value, this);
    }
};

int main() {
    Mediator mediator {};
    Participant p1 {mediator}, p2 {mediator};
    p1.say(3);
    cout << p1.value << " " << p2.value << endl;
    p2.say(2);
    cout << p1.value << " " << p2.value << endl;
    return 0;
}
