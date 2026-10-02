#include "Game/AI/Action/actionPlayerWaterDivingJump.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWaterDivingJump::PlayerWaterDivingJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWaterDivingJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWaterDivingJump::leave_() {
    PlayerAction::leave_();
}

void PlayerWaterDivingJump::loadParams_() {
    getStaticParam(&mDiveSpeedF_s, "DiveSpeedF");
    getStaticParam(&mDiveHeight_s, "DiveHeight");
    getStaticParam(&mDiveSpeedDec_s, "DiveSpeedDec");
}

void PlayerWaterDivingJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerWaterDivingJump::isChangeable() const {
    return true;
}

bool PlayerWaterDivingJump::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround();
}

}  // namespace uking::action
