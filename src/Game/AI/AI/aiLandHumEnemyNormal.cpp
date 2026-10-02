#include "Game/AI/AI/aiLandHumEnemyNormal.h"

namespace uking::ai {

LandHumEnemyNormal::LandHumEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

LandHumEnemyNormal::~LandHumEnemyNormal() = default;

bool LandHumEnemyNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void LandHumEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void LandHumEnemyNormal::calc_() {
    EnemyNormal::calc_();
}

void LandHumEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void LandHumEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mTerrorIgnoreDist_s, "TerrorIgnoreDist");
    getStaticParam(&mExplosivesSearchDist_s, "ExplosivesSearchDist");
    getStaticParam(&mExplosivesSearchSpeed_s, "ExplosivesSearchSpeed");
    getStaticParam(&mExplosivesSearchAng_s, "ExplosivesSearchAng");
}

s32 LandHumEnemyNormal::m52(s32 idx) {
    static const s32 sTable[] = {0, 1, 2, 3, 9, 10, 4, 5, 6, 7, 8};
    return sTable[idx];
}

}  // namespace uking::ai
