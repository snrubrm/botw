#include "Game/AI/Behavior/behaviorSetIsAffectWeak.h"

namespace uking::behavior {

SetIsAffectWeak::SetIsAffectWeak(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetIsAffectWeak::~SetIsAffectWeak() = default;

bool SetIsAffectWeak::m6(sead::Heap* heap) {
    return true;
}

void SetIsAffectWeak::m7() {}

void SetIsAffectWeak::loadParams() {
    getStaticParam(&mIsAffect_s, "IsAffect");
}

}  // namespace uking::behavior
