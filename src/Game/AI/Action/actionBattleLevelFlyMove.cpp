#include "Game/AI/Action/actionBattleLevelFlyMove.h"

namespace uking::action {

BattleLevelFlyMove::BattleLevelFlyMove(const InitArg& arg) : BattleLevelFlyMoveBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
BattleLevelFlyMove::~BattleLevelFlyMove() {
    ;
}

void BattleLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleLevelFlyMoveBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
}

void BattleLevelFlyMove::loadParams_() {
    BattleLevelFlyMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
