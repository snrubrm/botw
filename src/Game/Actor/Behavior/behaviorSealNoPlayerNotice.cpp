#include "Game/Actor/Behavior/behaviorSealNoPlayerNotice.h"

namespace uking::behavior {

SealNoPlayerNotice::SealNoPlayerNotice(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SealNoPlayerNotice::~SealNoPlayerNotice() = default;

bool SealNoPlayerNotice::init_(sead::Heap* heap) {
    return true;
}

void SealNoPlayerNotice::calc() {}

void SealNoPlayerNotice::loadParams() {
    getAITreeVariable(&mSealNoPlayerAwnRequestCount_a, "SealNoPlayerAwnRequestCount");
}

void SealNoPlayerNotice::enter() {
    ++*mSealNoPlayerAwnRequestCount_a;
}

void SealNoPlayerNotice::leave() {
    --*mSealNoPlayerAwnRequestCount_a;
}

}  // namespace uking::behavior
