#include "Game/AI/Behavior/behaviorSetBattleNodeBasisSelfPosBattle.h"

namespace uking::behavior {

SetBattleNodeBasisSelfPosBattle::SetBattleNodeBasisSelfPosBattle(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

SetBattleNodeBasisSelfPosBattle::~SetBattleNodeBasisSelfPosBattle() = default;

bool SetBattleNodeBasisSelfPosBattle::m6(sead::Heap* heap) {
    return true;
}

void SetBattleNodeBasisSelfPosBattle::m7() {}

void SetBattleNodeBasisSelfPosBattle::loadParams() {
    getStaticParam(&mSetFlag_s, "SetFlag");
}

}  // namespace uking::behavior
