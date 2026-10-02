#include "Game/AI/AI/aiAssassinFieldShooterBattleBase.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

AssassinFieldShooterBattleBase::AssassinFieldShooterBattleBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AssassinFieldShooterBattleBase::~AssassinFieldShooterBattleBase() = default;

bool AssassinFieldShooterBattleBase::init_(sead::Heap* heap) {
    const s32 tired_time = *mTiredTime_s;
    const s32 tired_time2 = tired_time * 1.2f;
    _74 = sead::Mathi::min(tired_time, tired_time2);
    _78 = sead::Mathi::max(tired_time, tired_time2);
    return true;
}

void AssassinFieldShooterBattleBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AssassinFieldShooterBattleBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AssassinFieldShooterBattleBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTiredTime_s, "TiredTime");
    getStaticParam(&mWarpDistNear_s, "WarpDistNear");
    getStaticParam(&mWarpDistFar_s, "WarpDistFar");
    getStaticParam(&mTerritoryDist_s, "TerritoryDist");
    getStaticParam(&mTiredGrHeight_s, "TiredGrHeight");
    getStaticParam(&mIntervalIntensity_s, "IntervalIntensity");
}

}  // namespace uking::ai
