#include "Game/Actor/Behavior/behaviorIgnoreGiantArmorCondition.h"

namespace uking::behavior {

IgnoreGiantArmorCondition::IgnoreGiantArmorCondition(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

IgnoreGiantArmorCondition::~IgnoreGiantArmorCondition() = default;

bool IgnoreGiantArmorCondition::init_(sead::Heap* heap) {
    return true;
}

void IgnoreGiantArmorCondition::calc() {}

void IgnoreGiantArmorCondition::loadParams() {
    getAITreeVariable(&mIgnoreGiantArmorCondition_a, "IgnoreGiantArmorCondition");
}

void IgnoreGiantArmorCondition::enter() {
    *mIgnoreGiantArmorCondition_a = true;
}

void IgnoreGiantArmorCondition::leave() {
    *mIgnoreGiantArmorCondition_a = false;
}

}  // namespace uking::behavior
