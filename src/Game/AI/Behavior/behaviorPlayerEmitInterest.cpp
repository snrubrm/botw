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

void PlayerEmitInterest::m7() {
    auto* player = sead::DynamicCast<ksys::act::PlayerBase>(mActor);
    if (!player)
        return;
    auto* unit = mActor->get548();
    if (player->_c44.isOnBit(6))
        unit->emitInterest(*mLevelNaked_s, *mIsTargetNPC_s);
    else
        unit->emitInterest(*mLevelBase_s, *mIsTargetNPC_s);
}

}  // namespace uking::behavior
