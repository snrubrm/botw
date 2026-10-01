#include "Game/AI/Action/actionLiftTurn.h"

namespace uking::action {

LiftTurn::LiftTurn(const InitArg& arg) : TurnBase(arg) {}

bool LiftTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void LiftTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
    playAS("LiftTurn", false, 0, 0, -1.0f);
}

void LiftTurn::leave_() {
    TurnBase::leave_();
}

void LiftTurn::loadParams_() {
    TurnBase::loadParams_();
}

void LiftTurn::calc_() {
    TurnBase::calc_();
}

}  // namespace uking::action
