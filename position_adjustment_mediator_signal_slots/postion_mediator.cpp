#include "position_mediator.h"

void PositionMediator::add_slot(Strategy &strategy, float weight) {
    slots.emplace_back(&strategy, weight);
    strategy.trade_signal.connect(
            [&](float lots, size_t origin_id){
                on_trade_event(lots, origin_id);
            });
    eff_pos_signal.connect(
            [&](float eff_pos){
                float& dest_weight = slots[strategy.id].second;
                strategy.on_eff_pos_event(eff_pos / dest_weight);
                strategy.print_state();
            });
}

void PositionMediator::on_trade_event(float lots, size_t origin_id) {
    float& origin_weight = slots[origin_id].second;
    eff_pos_signal(origin_weight * lots);
}