#include "Game/AI/AI/aiLandHumGourmandEnemyNormal.h"

namespace uking::ai {

LandHumGourmandEnemyNormal::LandHumGourmandEnemyNormal(const InitArg& arg)
    : LandHumEnemyNormal(arg) {}

LandHumGourmandEnemyNormal::~LandHumGourmandEnemyNormal() = default;

bool LandHumGourmandEnemyNormal::init_(sead::Heap* heap) {
    return LandHumEnemyNormal::init_(heap);
}

void LandHumGourmandEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    LandHumEnemyNormal::enter_(params);
    sub_7100472538();
    _418 = ksys::Timer(0, 0);
}

void LandHumGourmandEnemyNormal::calc_() {
    LandHumEnemyNormal::calc_();
}

void LandHumGourmandEnemyNormal::leave_() {
    LandHumEnemyNormal::leave_();
}

void LandHumGourmandEnemyNormal::loadParams_() {
    LandHumEnemyNormal::loadParams_();
    getStaticParam(&mRefindBaitTime_s, "RefindBaitTime");
    getStaticParam(&mEatArea_s, "EatArea");
    getStaticParam(&mEatNavType_s, "EatNavType");
    getAITreeVariable(&mTargetBaitActorLink_a, "TargetBaitActorLink");
    getAITreeVariable(&mIsTrgChangeUnderWaterState_a, "IsTrgChangeUnderWaterState");
}

void LandHumGourmandEnemyNormal::m35() {
    if (*mIsTrgChangeUnderWaterState_a) {
        m36();
        return;
    }
    EnemyNormal::m35();
}

s32 LandHumGourmandEnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 11, 2, 3, 9, 4, 5, 6, 7, 8, 10};
    return sTable[idx];
}

}  // namespace uking::ai
