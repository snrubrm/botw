#include "Game/AI/AI/aiWaistRotEnemyArrowAttack.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

WaistRotEnemyArrowAttack::WaistRotEnemyArrowAttack(const InitArg& arg)
    : EnemyBaseArrowAttack(arg) {}

WaistRotEnemyArrowAttack::~WaistRotEnemyArrowAttack() = default;

bool WaistRotEnemyArrowAttack::init_(sead::Heap* heap) {
    return EnemyBaseArrowAttack::init_(heap);
}

void WaistRotEnemyArrowAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _64 = 0.0f;
    _58 = sead::Vector3f::zero;
    EnemyBaseArrowAttack::enter_(params);
}

void WaistRotEnemyArrowAttack::calc_() {
    EnemyBaseArrowAttack::calc_();
}

void WaistRotEnemyArrowAttack::leave_() {
    EnemyBaseArrowAttack::leave_();
}

void WaistRotEnemyArrowAttack::loadParams_() {
    EnemyBaseArrowAttack::loadParams_();
    getStaticParam(&mRandomPredictFrame_s, "RandomPredictFrame");
}

void WaistRotEnemyArrowAttack::m35() {
    if (*mRandomPredictFrame_s > 0) {
        _64 = *mRandomPredictFrame_s * sead::GlobalRandom::instance()->getF32();
        _58 = sub_71005D9548(mActor);
    }
    EnemyBaseArrowAttack::m35();
}

void WaistRotEnemyArrowAttack::m37() {}

}  // namespace uking::ai
