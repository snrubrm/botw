#include "Game/AI/Behavior/behaviorInvalidateCondition.h"

namespace uking::behavior {

InvalidateCondition::InvalidateCondition(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

InvalidateCondition::~InvalidateCondition() = default;

bool InvalidateCondition::m6(sead::Heap* heap) {
    return true;
}

void InvalidateCondition::m7() {}

void InvalidateCondition::loadParams() {
    getStaticParam(&mInvalidBurn_s, "InvalidBurn");
    getStaticParam(&mInvalidIce_s, "InvalidIce");
    getStaticParam(&mInvalidElectric_s, "InvalidElectric");
}

}  // namespace uking::behavior
