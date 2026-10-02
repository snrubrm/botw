#include "Game/AI/Action/actionPlayerWaterFallJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWaterFallJump::PlayerWaterFallJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWaterFallJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWaterFallJump::leave_() {
    PlayerAction::leave_();
}

void PlayerWaterFallJump::loadParams_() {
    getStaticParam(&mJumpSpeedF_s, "JumpSpeedF");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mJumpHeightWaterRemain_s, "JumpHeightWaterRemain");
    getStaticParam(&mJumpHeightWithZora_s, "JumpHeightWithZora");
}

void PlayerWaterFallJump::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (mActor->getVelocity().y <= 0.01f)
        setFinished();
}

bool PlayerWaterFallJump::isChangeable() const {
    return false;
}

}  // namespace uking::action
