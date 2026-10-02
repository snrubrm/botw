#include "Game/AI/Action/actionPlayerSwimWait.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSwimWait::PlayerSwimWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSwimWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimWait::leave_() {}

void PlayerSwimWait::loadParams_() {
    getStaticParam(&mEnergyWait_s, "EnergyWait");
    getStaticParam(&mDecSpeedRate_s, "DecSpeedRate");
}

void PlayerSwimWait::calc_() {
    PlayerAction::calc_();
}

bool PlayerSwimWait::isChangeable() const {
    return true;
}

bool PlayerSwimWait::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->_209c > 0.05f;
}

}  // namespace uking::action
