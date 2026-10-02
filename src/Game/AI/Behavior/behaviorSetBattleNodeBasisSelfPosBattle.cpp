#include "Game/AI/Behavior/behaviorSetBattleNodeBasisSelfPosBattle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

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

// NON_MATCHING: the original keeps the three cases as branches (ours becomes a lookup table)
void SetBattleNodeBasisSelfPosBattle::m8() {
    auto* control = mActor->sub_71011D8A10();
    if (!control)
        return;
    switch (*mSetFlag_s) {
    case 0:
        control->_8c |= 0xc;
        break;
    case 1:
        control->_8c |= 0x4;
        break;
    case 2:
        control->_8c |= 0x8;
        break;
    }
}

// NON_MATCHING: the original keeps the three cases as branches (ours becomes a lookup table)
void SetBattleNodeBasisSelfPosBattle::m9() {
    auto* control = mActor->sub_71011D8A10();
    if (!control)
        return;
    switch (*mSetFlag_s) {
    case 0:
        control->_8c &= ~0xc;
        break;
    case 1:
        control->_8c &= ~0x4;
        break;
    case 2:
        control->_8c &= ~0x8;
        break;
    }
}

}  // namespace uking::behavior
