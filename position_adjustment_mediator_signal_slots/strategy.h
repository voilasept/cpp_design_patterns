#ifndef POSITION_ADJUSTMENT_MEDIATOR_SIGNAL_SLOTS_STRATEGY_H
#define POSITION_ADJUSTMENT_MEDIATOR_SIGNAL_SLOTS_STRATEGY_H

#include <string>
#include "position_mediator.h"
using namespace std;

class PositionMediator;

class Strategy{
public:
    static size_t next_id;
    static size_t get_next_id();

    Strategy(string symbol);

    const string symbol;
    const size_t id;

    float position = 0;     // true position
    float eff_position = 0; // effective position

    boost::signals2::signal<void(float, size_t)> trade_signal {};
    void on_trade_event(float lots);    // delta lots, emits to mediator
    void on_eff_pos_event(float eff_lots);  // delta eff_lots, from mediator
    void print_state() const;
};


#endif //POSITION_ADJUSTMENT_MEDIATOR_SIGNAL_SLOTS_STRATEGY_H
