#include "Game/AI/Action/actionPlayerZoraJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerZoraJump::PlayerZoraJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerZoraJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerZoraJump::leave_() {}

void PlayerZoraJump::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void PlayerZoraJump::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (mActor->getVelocity().y <= 0.01f)
        setFinished();
}

bool PlayerZoraJump::isChangeable() const {
    return true;
}

}  // namespace uking::action
