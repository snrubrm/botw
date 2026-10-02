#include "Game/AI/Behavior/behaviorPlayerEmitInterest.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

PlayerEmitInterest::PlayerEmitInterest(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

PlayerEmitInterest::~PlayerEmitInterest() = default;

bool PlayerEmitInterest::m6(sead::Heap* heap) {
    return true;
}

void PlayerEmitInterest::m8() {}

void PlayerEmitInterest::m9() {}

void PlayerEmitInterest::loadParams() {
    getStaticParam(&mLevelBase_s, "LevelBase");
    getStaticParam(&mLevelNaked_s, "LevelNaked");
    getStaticParam(&mIsTargetNPC_s, "IsTargetNPC");
}

// NON_MATCHING: the original reads IsTargetNPC in both branches, before updating the unit
void PlayerEmitInterest::m7() {
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor);
    if (!player)
        return;
    auto* unit = mActor->get548();
    const int level = player->_c44.isOnBit(6) ? *mLevelNaked_s : *mLevelBase_s;
    if (unit->_18._48 < level)
        unit->_18._48 = level;
    unit->_18._44 |= *mIsTargetNPC_s;
}

}  // namespace uking::behavior
