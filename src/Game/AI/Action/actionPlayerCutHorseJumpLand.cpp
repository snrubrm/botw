#include "Game/AI/Action/actionPlayerCutHorseJumpLand.h"

namespace uking::action {

PlayerCutHorseJumpLand::PlayerCutHorseJumpLand(const InitArg& arg) : PlayerAction(arg) {}

void PlayerCutHorseJumpLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutHorseJumpLand::leave_() {
    PlayerAction::leave_();
}

void PlayerCutHorseJumpLand::calc_() {
    PlayerAction::calc_();
}

bool PlayerCutHorseJumpLand::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
