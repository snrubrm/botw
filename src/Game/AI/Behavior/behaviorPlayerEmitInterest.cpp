#include "Game/AI/Behavior/behaviorPlayerEmitInterest.h"

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

}  // namespace uking::behavior
