#include "Game/AI/Action/actionBattleCloseSlippedWalk.h"

namespace uking::action {

BattleCloseSlippedWalk::BattleCloseSlippedWalk(const InitArg& arg)
    : BattleCloseSlippedWalkBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
BattleCloseSlippedWalk::~BattleCloseSlippedWalk() {
    ;
}

bool BattleCloseSlippedWalk::init_(sead::Heap* heap) {
    return BattleCloseSlippedWalkBase::init_(heap);
}

void BattleCloseSlippedWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BattleCloseSlippedWalkBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void BattleCloseSlippedWalk::leave_() {
    BattleCloseSlippedWalkBase::leave_();
}

void BattleCloseSlippedWalk::loadParams_() {
    BattleCloseSlippedWalkBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void BattleCloseSlippedWalk::calc_() {
    BattleCloseSlippedWalkBase::calc_();
}

}  // namespace uking::action
