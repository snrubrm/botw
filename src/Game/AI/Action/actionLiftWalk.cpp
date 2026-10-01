#include "Game/AI/Action/actionLiftWalk.h"

namespace uking::action {

LiftWalk::LiftWalk(const InitArg& arg) : MoveBase(arg) {}

bool LiftWalk::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void LiftWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
    playAS("LiftWalk", false, 0, 0, -1.0f);
}

void LiftWalk::leave_() {
    MoveBase::leave_();
}

void LiftWalk::loadParams_() {
    MoveBase::loadParams_();
}

void LiftWalk::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
