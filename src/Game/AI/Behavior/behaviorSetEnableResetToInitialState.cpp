#include "Game/AI/Behavior/behaviorSetEnableResetToInitialState.h"

namespace uking::behavior {

SetEnableResetToInitialState::SetEnableResetToInitialState(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetEnableResetToInitialState::~SetEnableResetToInitialState() = default;

bool SetEnableResetToInitialState::m6(sead::Heap* heap) {
    return true;
}

void SetEnableResetToInitialState::m8() {
    _30 = ksys::Timer(30.0f, 30.0f);
}

void SetEnableResetToInitialState::m9() {}

void SetEnableResetToInitialState::loadParams() {

}

}  // namespace uking::behavior
