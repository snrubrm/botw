#include "Game/AI/Action/actionPlayerGuardJust.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerGuardJust::PlayerGuardJust(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuardJust::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x4000000);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("GuardJust", true, -1.0f);
}

void PlayerGuardJust::leave_() {
    PlayerAction::leave_();
}

void PlayerGuardJust::loadParams_() {
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
}

void PlayerGuardJust::calc_() {
    PlayerAction::calc_();
}

bool PlayerGuardJust::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
