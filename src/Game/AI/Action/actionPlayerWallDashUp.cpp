#include "Game/AI/Action/actionPlayerWallDashUp.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerWallDashUp::PlayerWallDashUp(const InitArg& arg) : PlayerAction(arg) {}

void PlayerWallDashUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWallDashUp::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x80000);
}

void PlayerWallDashUp::loadParams_() {
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mMinSpeedF_s, "MinSpeedF");
    getStaticParam(&mMaxSpeedF_s, "MaxSpeedF");
}

void PlayerWallDashUp::calc_() {
    PlayerAction::calc_();
}

bool PlayerWallDashUp::isChangeable() const {
    return true;
}

}  // namespace uking::action
