#include "Game/AI/Action/actionPlayerLadderUpEnd.h"

namespace uking::action {

PlayerLadderUpEnd::PlayerLadderUpEnd(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderUpEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderUpEnd::leave_() {}

void PlayerLadderUpEnd::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderUpEnd::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
