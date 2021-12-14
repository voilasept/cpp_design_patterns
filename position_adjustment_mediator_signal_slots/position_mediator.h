#ifndef POSITION_ADJUSTMENT_MEDIATOR_SIGNAL_SLOTS_POSITION_MEDIATOR_H
#define POSITION_ADJUSTMENT_MEDIATOR_SIGNAL_SLOTS_POSITION_MEDIATOR_H

#include <iostream>
#include <string>
#include <boost/signals2.hpp>
#include "strategy.h"
using namespace std;

class Strategy;

class PositionMediator{
public:
    PositionMediator() = default;
    boost::signals2::signal<void(float)> eff_pos_signal {};
    void add_slot(Strategy& strategy, float weight);
    void on_trade_event(float lots, size_t origin_id);
    vector<std::pair<Strategy*, float>> slots;  // {strategy, weight}
};


#endif //POSITION_ADJUSTMENT_MEDIATOR_SIGNAL_SLOTS_POSITION_MEDIATOR_H
