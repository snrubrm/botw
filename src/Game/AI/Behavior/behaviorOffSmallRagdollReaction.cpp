#include "Game/AI/Behavior/behaviorOffSmallRagdollReaction.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

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

void OffSmallRagdollReaction::m8() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    _28 = actor->_a68 & 1;
    if (_28)
        actor->_a68 &= ~1;
}

void OffSmallRagdollReaction::m9() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    if (_28)
        actor->_a68 |= 1;
}

}  // namespace uking::behavior
