#include "Game/AI/Action/actionPlayerLadderUpStart.h"

namespace uking::action {

PlayerLadderUpStart::PlayerLadderUpStart(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderUpStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderUpStart::leave_() {}

void PlayerLadderUpStart::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerLadderUpStart::calc_() {
    PlayerAction::calc_();
}

bool PlayerLadderUpStart::isChangeable() const {
    return false;
}

}  // namespace uking::action
