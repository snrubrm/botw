#include "Game/AI/Action/actionPlayerSwimJump.h"

namespace uking::action {

PlayerSwimJump::PlayerSwimJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimJump::leave_() {}

void PlayerSwimJump::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mEnergyJump_s, "EnergyJump");
}

void PlayerSwimJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimJump::isChangeable() const {
    return true;
}

}  // namespace uking::action
