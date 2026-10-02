#include "Game/AI/Behavior/behaviorDisableSkipCalcCloth.h"

namespace uking::behavior {

DisableSkipCalcCloth::DisableSkipCalcCloth(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableSkipCalcCloth::~DisableSkipCalcCloth() = default;

bool DisableSkipCalcCloth::m6(sead::Heap* heap) {
    return true;
}

void DisableSkipCalcCloth::m7() {}

void DisableSkipCalcCloth::loadParams() {

}

}  // namespace uking::behavior
