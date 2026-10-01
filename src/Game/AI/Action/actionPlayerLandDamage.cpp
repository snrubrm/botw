#include "Game/AI/Action/actionPlayerLandDamage.h"

namespace uking::action {

PlayerLandDamage::PlayerLandDamage(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLandDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLandDamage::leave_() {}

void PlayerLandDamage::loadParams_() {
    getStaticParam(&mWaitTimeMin_s, "WaitTimeMin");
    getStaticParam(&mWaitTimeMax_s, "WaitTimeMax");
    getStaticParam(&mDeadHeight_s, "DeadHeight");
    getStaticParam(&mDamageMin_s, "DamageMin");
}

void PlayerLandDamage::calc_() {
    PlayerAction::calc_();
}

bool PlayerLandDamage::isChangeable() const {
    return true;
}

}  // namespace uking::action
