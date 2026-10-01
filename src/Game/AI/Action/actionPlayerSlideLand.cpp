#include "Game/AI/Action/actionPlayerSlideLand.h"

namespace uking::action {

PlayerSlideLand::PlayerSlideLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSlideLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSlideLand::leave_() {
    PlayerAction::leave_();
}

void PlayerSlideLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerSlideLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
