#include "Game/AI/AI/aiSwarmRoot.h"
#include "Game/Actor/actSwarm.h"
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::ai {

SwarmRoot::SwarmRoot(const InitArg& arg) : EnemyRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SwarmRoot::~SwarmRoot() {
    ;
}

bool SwarmRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void SwarmRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void SwarmRoot::calc_() {
    EnemyRoot::calc_();
}

void SwarmRoot::leave_() {
    EnemyRoot::leave_();
}

void SwarmRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

bool SwarmRoot::m35() {
    auto* damage_mgr = mActor->getDamageMgr();
    if (damage_mgr && damage_mgr->getField54() == 6)
        return false;

    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (swarm && swarm->_1614)
        return true;

    return EnemyRoot::m35();
}

}  // namespace uking::ai
