#include <iostream>
#include <map>
#include "multiton.h"
using namespace std;

enum class Tier{
    Best,
    Good,
    Bad
};

class Printer{
public:
    Printer(){
        cout << "created" << endl;
    }
    ~Printer(){
        cout << "destroyed" << endl;
    }
};

int main() {
    typedef Multiton<Printer, Tier> MetaPrinter;    // never get instantiated
    auto best_printer = MetaPrinter::get(Tier::Best);
    auto best_printer2 = MetaPrinter::get(Tier::Best);
    auto bad_printer = MetaPrinter::get(Tier::Bad);
    cout << best_printer << endl
         << best_printer2 << endl
         << bad_printer << endl;
    return 0;
}
