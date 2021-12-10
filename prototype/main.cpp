#include <iostream>
#include <string>
#include <utility>
#include <memory>

using namespace std;

struct Address{
public:
    string street;
    Address() = default;
    explicit Address(string street):street(std::move(street)){}
    Address(const Address& other){
        street = other.street;
    }
    friend ostream& operator<<(ostream& os, const Address& _address) {
        os << _address.street << endl;
        return os;
    }
};

class Contact{
    friend class ContactFactory;
private:
    Contact() = default;
    Contact(string name, string street):name(std::move(name)), address(new Address{move(street)}){}
public:
    string name {};
    Address *address {nullptr};
    Contact(const Contact& other):name(other.name), address(new Address {*other.address}){}
    friend ostream& operator<<(ostream& os, const Contact& contact){
        os << contact.name << ": " << *contact.address << endl;
        return os;
    }
};

class ContactFactory{
public:
    ContactFactory() = default;
    const Contact office_address = Contact("", "353 N Clark");
    static Contact makeOld(string name){
        static const Address old_address = Address("531 W Deming Place");
        auto contact = Contact(move(name), old_address.street);
        return contact;
    }
    static Contact makeNew(string name){
        const Address new_address = Address("920 W Schubert Ave");
        auto contact = Contact(move(name), new_address.street);
        return contact;
    }
    static unique_ptr<Contact> makeByPrototype(string name, const Contact& prototype){
        unique_ptr<Contact> contact = make_unique<Contact>(prototype);
        contact->name = move(name);
        return contact;
    }
};


int main() {
    auto p1 = ContactFactory::makeOld("Han");
    auto p2 = ContactFactory::makeNew("Ran");
    cout << p1 << p2 << endl;
    auto cf = ContactFactory();
    auto p3 = ContactFactory::makeByPrototype("Harry", cf.office_address);
    cout << *p3 << endl;
    return 0;
}
