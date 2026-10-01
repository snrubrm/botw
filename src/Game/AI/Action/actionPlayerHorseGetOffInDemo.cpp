#include "Game/AI/Action/actionPlayerHorseGetOffInDemo.h"

namespace uking::action {

PlayerHorseGetOffInDemo::PlayerHorseGetOffInDemo(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHorseGetOffInDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHorseGetOffInDemo::leave_() {}

void PlayerHorseGetOffInDemo::calc_() {
    PlayerAction::calc_();
}

bool PlayerHorseGetOffInDemo::isChangeable() const {
    return false;
}

}  // namespace uking::action
