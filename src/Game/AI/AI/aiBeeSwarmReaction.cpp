#include "Game/AI/AI/aiBeeSwarmReaction.h"
#include "Game/Actor/actSwarm.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BeeSwarmReaction::BeeSwarmReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BeeSwarmReaction::~BeeSwarmReaction() = default;

bool BeeSwarmReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BeeSwarmReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm) {
        setFailed();
        return;
    }
    swarm->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    _38 = true;
    *mActor->getLife() = mActor->getMaxLife();
    sub_710032AF18();
}

bool BeeSwarmReaction::sub_710032B414() {
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        if (actor->m151(3))
            return true;
        if (actor->m151(4))
            return true;
        if (actor->m151(2))
            return true;
    }
    auto* damage_mgr = mActor->getDamageMgr();
    if (!damage_mgr)
        return false;
    const s32 type = damage_mgr->getField54();
    const s32 other = damage_mgr->getField50();
    if (type == 3 || type == 4 || type == 18)
        return true;
    return u32(other - 9) < 3;
}

void BeeSwarmReaction::leave_() {
    *mActor->getLife() = mActor->getMaxLife();
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

void BeeSwarmReaction::loadParams_() {}

}  // namespace uking::ai
