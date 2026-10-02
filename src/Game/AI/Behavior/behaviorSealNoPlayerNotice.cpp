#include "Game/AI/Behavior/behaviorSealNoPlayerNotice.h"

namespace uking::behavior {

SealNoPlayerNotice::SealNoPlayerNotice(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SealNoPlayerNotice::~SealNoPlayerNotice() = default;

bool SealNoPlayerNotice::m6(sead::Heap* heap) {
    return true;
}

void SealNoPlayerNotice::m7() {}

void SealNoPlayerNotice::loadParams() {
    getAITreeVariable(&mSealNoPlayerAwnRequestCount_a, "SealNoPlayerAwnRequestCount");
}

}  // namespace uking::behavior
