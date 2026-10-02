#include "Game/AI/Action/actionPlayerStepGuardJust.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerStepGuardJust::PlayerStepGuardJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerStepGuardJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerStepGuardJust::leave_() {}

void PlayerStepGuardJust::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerStepGuardJust::calc_() {
    PlayerAction::calc_();
}

bool PlayerStepGuardJust::isChangeable() const {
    return _1c;
}

bool PlayerStepGuardJust::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
