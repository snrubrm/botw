#include "Game/AI/Behavior/behaviorDisableWeakPointActor.h"

namespace uking::behavior {

DisableWeakPointActor::DisableWeakPointActor(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool DisableWeakPointActor::m6(sead::Heap* heap) {
    return true;
}

void DisableWeakPointActor::m7() {}

void DisableWeakPointActor::loadParams() {
    getStaticParam(&mWeakPointKey_s, "WeakPointKey");
}

}  // namespace uking::behavior
