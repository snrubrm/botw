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

void WaistRotEnemyArrowAttack::m36() {
    if (!isCurrentChild("攻撃")) {
        EnemyBaseArrowAttack::m36();
        return;
    }

    if (_64 > 0.0f) {
        const f32 rate = 0.9f;
        _58 *= rate;
        _58.setScaleAdd(1.0f - rate, sub_71005D9548(mActor), _58);
        sead::Vector3f pos;
        pos.setScaleAdd(_64, _58, sub_71005D93CC(mActor));
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
    } else {
        getCurrentChild()->setDynamicParam(sub_71005D93CC(mActor), "TargetPos");
    }
}

void WaistRotEnemyArrowAttack::m37() {}

}  // namespace uking::ai
