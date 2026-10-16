#include "Game/Actor/Behavior/behaviorOffSmallRagdollReaction.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::behavior {

OffSmallRagdollReaction::OffSmallRagdollReaction(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

OffSmallRagdollReaction::~OffSmallRagdollReaction() = default;

bool OffSmallRagdollReaction::init_(sead::Heap* heap) {
    return true;
}

void OffSmallRagdollReaction::calc() {}

void OffSmallRagdollReaction::loadParams() {

}

void OffSmallRagdollReaction::enter() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    _28 = actor->_a68 & 1;
    if (_28)
        actor->_a68 &= ~1;
}

void OffSmallRagdollReaction::leave() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return;
    if (_28)
        actor->_a68 |= 1;
}

}  // namespace uking::behavior
