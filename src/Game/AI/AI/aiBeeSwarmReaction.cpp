#include "Game/AI/AI/aiBeeSwarmReaction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BeeSwarmReaction::BeeSwarmReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BeeSwarmReaction::~BeeSwarmReaction() = default;

bool BeeSwarmReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BeeSwarmReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BeeSwarmReaction::leave_() {
    *mActor->getLife() = mActor->getMaxLife();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

void BeeSwarmReaction::loadParams_() {}

}  // namespace uking::ai
