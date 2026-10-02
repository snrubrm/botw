#include "Game/AI/Action/actionBattleCloseLevelFlyMove.h"

namespace uking::action {

BattleCloseLevelFlyMove::BattleCloseLevelFlyMove(const InitArg& arg)
    : BattleCloseLevelFlyMoveBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
BattleCloseLevelFlyMove::~BattleCloseLevelFlyMove() {
    ;
}

bool BattleCloseLevelFlyMove::init_(sead::Heap* heap) {
    return BattleCloseLevelFlyMoveBase::init_(heap);
}

void BattleCloseLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseLevelFlyMoveBase::enter_(params);
}

void BattleCloseLevelFlyMove::leave_() {
    BattleCloseLevelFlyMoveBase::leave_();
}

void BattleCloseLevelFlyMove::loadParams_() {
    BattleCloseLevelFlyMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BattleCloseLevelFlyMove::calc_() {
    BattleCloseLevelFlyMoveBase::calc_();
}

}  // namespace uking::action
