#include "Game/AI/Behavior/behaviorOffSmallRagdollReaction.h"

namespace uking::behavior {

OffSmallRagdollReaction::OffSmallRagdollReaction(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

OffSmallRagdollReaction::~OffSmallRagdollReaction() = default;

bool OffSmallRagdollReaction::m6(sead::Heap* heap) {
    return true;
}

void OffSmallRagdollReaction::m7() {}

void OffSmallRagdollReaction::loadParams() {

}

}  // namespace uking::behavior
