#include "Game/AI/Behavior/behaviorOnAnimalSupportNrmCalcFrontRay.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

OnAnimalSupportNrmCalcFrontRay::OnAnimalSupportNrmCalcFrontRay(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

OnAnimalSupportNrmCalcFrontRay::~OnAnimalSupportNrmCalcFrontRay() = default;

bool OnAnimalSupportNrmCalcFrontRay::m6(sead::Heap* heap) {
    return true;
}

void OnAnimalSupportNrmCalcFrontRay::m7() {}

void OnAnimalSupportNrmCalcFrontRay::m8() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        if (auto* support = enemy->_1198)
            support->_28 |= 2;
    }
}

void OnAnimalSupportNrmCalcFrontRay::m9() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        if (auto* support = enemy->_1198)
            support->_28 &= ~2;
    }
}

void OnAnimalSupportNrmCalcFrontRay::loadParams() {

}

}  // namespace uking::behavior
