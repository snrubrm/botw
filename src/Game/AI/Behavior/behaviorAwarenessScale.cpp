#include "Game/AI/Behavior/behaviorAwarenessScale.h"

namespace uking::behavior {

AwarenessScale::AwarenessScale(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AwarenessScale::~AwarenessScale() = default;

bool AwarenessScale::m6(sead::Heap* heap) {
    return true;
}

void AwarenessScale::m7() {}

void AwarenessScale::loadParams() {
    getStaticParam(&mSight_s, "Sight");
    getStaticParam(&mHearing_s, "Hearing");
    getStaticParam(&mTerror_s, "Terror");
    getStaticParam(&mWorry_s, "Worry");
}

}  // namespace uking::behavior
