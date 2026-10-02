#include "Game/AI/Behavior/behaviorSetIsCalcSkipProhibited.h"

namespace uking::behavior {

SetIsCalcSkipProhibited::SetIsCalcSkipProhibited(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetIsCalcSkipProhibited::~SetIsCalcSkipProhibited() = default;

bool SetIsCalcSkipProhibited::m6(sead::Heap* heap) {
    return true;
}

void SetIsCalcSkipProhibited::m7() {}

void SetIsCalcSkipProhibited::loadParams() {

}

}  // namespace uking::behavior
