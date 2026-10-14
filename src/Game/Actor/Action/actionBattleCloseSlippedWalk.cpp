#include "Game/Actor/Action/actionBattleCloseSlippedWalk.h"

namespace uking::action {

BattleCloseSlippedWalk::BattleCloseSlippedWalk(const InitArg& arg)
    : BattleCloseSlippedMoveBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
BattleCloseSlippedWalk::~BattleCloseSlippedWalk() {
    ;
}

bool BattleCloseSlippedWalk::init_(sead::Heap* heap) {
    return BattleCloseSlippedMoveBase::init_(heap);
}

void BattleCloseSlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseSlippedMoveBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void BattleCloseSlippedWalk::leave_() {
    BattleCloseSlippedMoveBase::leave_();
}

void BattleCloseSlippedWalk::loadParams_() {
    BattleCloseSlippedMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BattleCloseSlippedWalk::calc_() {
    BattleCloseSlippedMoveBase::calc_();
}

}  // namespace uking::action
