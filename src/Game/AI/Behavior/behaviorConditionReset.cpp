#include "Game/AI/Behavior/behaviorConditionReset.h"

namespace uking::behavior {

ConditionReset::ConditionReset(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ConditionReset::~ConditionReset() = default;

bool ConditionReset::m6(sead::Heap* heap) {
    return true;
}

void ConditionReset::m7() {}

void ConditionReset::m9() {}

void ConditionReset::loadParams() {
    getStaticParam(&mIsResetBurn_s, "IsResetBurn");
    getStaticParam(&mIsResetIce_s, "IsResetIce");
    getStaticParam(&mIsResetElectric_s, "IsResetElectric");
}

}  // namespace uking::behavior
