#include "Game/Actor/Behavior/behaviorHorseSwitchAttRideBehavior.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

HorseSwitchAttRideBehavior::HorseSwitchAttRideBehavior(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

HorseSwitchAttRideBehavior::~HorseSwitchAttRideBehavior() = default;

bool HorseSwitchAttRideBehavior::init_(sead::Heap* heap) {
    return true;
}

void HorseSwitchAttRideBehavior::calc() {}

void HorseSwitchAttRideBehavior::loadParams() {

}

void HorseSwitchAttRideBehavior::enter() {
    auto* attention = mActor->getAttention();
    if (!attention)
        return;
    auto* ride = attention->getClientByName("Ride");
    if (!ride)
        return;
    auto* ride2 = attention->getClientByName("Ride2");
    if (!ride2)
        return;
    ride->disable();
    ride2->enable();
}

void HorseSwitchAttRideBehavior::leave() {
    auto* attention = mActor->getAttention();
    if (!attention)
        return;
    auto* ride = attention->getClientByName("Ride");
    if (!ride)
        return;
    auto* ride2 = attention->getClientByName("Ride2");
    if (!ride2)
        return;
    if (ride2->isEnabled()) {
        ride2->disable();
        ride->enable();
    }
}

}  // namespace uking::behavior
