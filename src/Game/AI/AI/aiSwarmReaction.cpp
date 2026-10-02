#include "Game/AI/AI/aiSwarmReaction.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SwarmReaction::SwarmReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmReaction::~SwarmReaction() = default;

bool SwarmReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwarmReaction::leave_() {
    *mActor->getLife() = mActor->getMaxLife();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

bool SwarmReaction::m34() {
    auto* damage_mgr = sub_710072BA90(mActor);
    if (damage_mgr && damage_mgr->getField54() != -1)
        return true;
    return false;
}

void SwarmReaction::m36() {
    changeChild("死亡");
}

void SwarmReaction::loadParams_() {}

}  // namespace uking::ai
