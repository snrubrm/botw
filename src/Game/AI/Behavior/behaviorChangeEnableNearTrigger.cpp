#include "Game/AI/Behavior/behaviorChangeEnableNearTrigger.h"

namespace uking::behavior {

ChangeEnableNearTrigger::ChangeEnableNearTrigger(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

ChangeEnableNearTrigger::~ChangeEnableNearTrigger() = default;

bool ChangeEnableNearTrigger::m6(sead::Heap* heap) {
    return true;
}

void ChangeEnableNearTrigger::m7() {}

void ChangeEnableNearTrigger::loadParams() {
    getStaticParam(&mEnable_s, "Enable");
    getStaticParam(&mIsRestoreWhenLeave_s, "IsRestoreWhenLeave");
}

}  // namespace uking::behavior
