#include "Game/AI/AI/aiEnemyChaseShield.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyChaseShield::EnemyChaseShield(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyChaseShield::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void EnemyChaseShield::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyChaseShield::loadParams_() {
    getDynamicParam(&mTargetWeapon_d, "TargetWeapon");
    getStaticParam(&mEquipItemSearchIdx_s, "EquipItemSearchIdx");
    getStaticParam(&mTurnAng_s, "TurnAng");
    getStaticParam(&mShieldReachDist_s, "ShieldReachDist");
}

}  // namespace uking::ai
