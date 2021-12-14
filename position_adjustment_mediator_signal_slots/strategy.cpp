#include <utility>
#include "strategy.h"

size_t Strategy::next_id = 0;
size_t Strategy::get_next_id() {
    return next_id++;
}

Strategy::Strategy(string symbol) :
    symbol(std::move(symbol)), id(Strategy::get_next_id()) {}

void Strategy::on_trade_event(float lots) {
    position += lots;
    trade_signal(lots, id);
}

void Strategy::on_eff_pos_event(float eff_lots) {
    eff_position += eff_lots;
}

void Strategy::print_state() const {
    cout << "Strategy " << id << " " << symbol
         << ": position " << position << " eff_position " << eff_position
         << endl;
}
