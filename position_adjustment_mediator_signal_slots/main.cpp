#include "strategy.h"
#include "position_mediator.h"
#include <iostream>
using namespace std;

int main() {
    auto fgbs = Strategy {"FGBS"};
    auto fgbm = Strategy {"FGBM"};
    auto fgbl = Strategy {"FGBL"};
    PositionMediator mediator;

    mediator.add_slot(fgbs, 0.2);
    mediator.add_slot(fgbm, 0.4);
    mediator.add_slot(fgbl, 1.0);

    fgbs.on_trade_event(10.);
    cout << endl;
    fgbm.on_trade_event(-8);

    return 0;
}
