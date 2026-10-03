#include "Game/AI/AI/aiLandHumEnemyThrowWeapon.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LandHumEnemyThrowWeapon::LandHumEnemyThrowWeapon(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LandHumEnemyThrowWeapon::~LandHumEnemyThrowWeapon() = default;

void LandHumEnemyThrowWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    changeToThrowWeapon();
}

void LandHumEnemyThrowWeapon::changeToThrowWeapon() {
    _64 = sub_710046CC20();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("武器投げ", &pack);
}

bool LandHumEnemyThrowWeapon::isChangeable() const {
    return false;
}

void LandHumEnemyThrowWeapon::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LandHumEnemyThrowWeapon::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mThrowWeaponNearDist_s, "ThrowWeaponNearDist");
    getStaticParam(&mWaitTimeMax_s, "WaitTimeMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
