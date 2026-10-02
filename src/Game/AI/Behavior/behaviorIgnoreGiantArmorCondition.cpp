#include "Game/AI/Behavior/behaviorIgnoreGiantArmorCondition.h"

namespace uking::behavior {

IgnoreGiantArmorCondition::IgnoreGiantArmorCondition(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

IgnoreGiantArmorCondition::~IgnoreGiantArmorCondition() = default;

bool IgnoreGiantArmorCondition::m6(sead::Heap* heap) {
    return true;
}

void IgnoreGiantArmorCondition::m7() {}

void IgnoreGiantArmorCondition::loadParams() {
    getAITreeVariable(&mIgnoreGiantArmorCondition_a, "IgnoreGiantArmorCondition");
}

void IgnoreGiantArmorCondition::m8() {
    *mIgnoreGiantArmorCondition_a = true;
}

void IgnoreGiantArmorCondition::m9() {
    *mIgnoreGiantArmorCondition_a = false;
}

}  // namespace uking::behavior
