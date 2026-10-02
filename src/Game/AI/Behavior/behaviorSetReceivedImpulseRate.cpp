#include "Game/AI/Behavior/behaviorSetReceivedImpulseRate.h"

namespace uking::behavior {

// NON_MATCHING: the delegate at 0x30 is not declared yet (placeholder bytes)
SetReceivedImpulseRate::SetReceivedImpulseRate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetReceivedImpulseRate::~SetReceivedImpulseRate() = default;

void SetReceivedImpulseRate::m7() {}

void SetReceivedImpulseRate::m8() {}

void SetReceivedImpulseRate::m9() {}

void SetReceivedImpulseRate::loadParams() {
    getStaticParam(&mImpulseRate_s, "ImpulseRate");
}

}  // namespace uking::behavior
