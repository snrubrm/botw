#include "Game/AI/Behavior/behaviorDisableGiantArmorWeakPoint.h"

namespace uking::behavior {

DisableGiantArmorWeakPoint::DisableGiantArmorWeakPoint(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

DisableGiantArmorWeakPoint::~DisableGiantArmorWeakPoint() = default;

bool DisableGiantArmorWeakPoint::m6(sead::Heap* heap) {
    return true;
}

void DisableGiantArmorWeakPoint::m7() {}

void DisableGiantArmorWeakPoint::loadParams() {
    getStaticParam(&mWeakPointIdx_s, "WeakPointIdx");
}

}  // namespace uking::behavior
