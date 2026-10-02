#include "Game/AI/Behavior/behaviorSetWindForceScale.h"

namespace uking::behavior {

SetWindForceScale::SetWindForceScale(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetWindForceScale::~SetWindForceScale() = default;

bool SetWindForceScale::m6(sead::Heap* heap) {
    return true;
}

void SetWindForceScale::m7() {}

void SetWindForceScale::m9() {}

void SetWindForceScale::loadParams() {
    getStaticParam(&mWindScale_s, "WindScale");
}

}  // namespace uking::behavior
