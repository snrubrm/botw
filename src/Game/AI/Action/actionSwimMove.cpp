#include "Game/AI/Action/actionSwimMove.h"

namespace uking::action {

SwimMove::SwimMove(const InitArg& arg) : SwimMoveBase(arg) {}

SwimMove::~SwimMove() = default;

bool SwimMove::init_(sead::Heap* heap) {
    return SwimMoveBase::init_(heap);
}

void SwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimMoveBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void SwimMove::leave_() {
    SwimMoveBase::leave_();
}

void SwimMove::loadParams_() {
    SwimMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SwimMove::calc_() {
    SwimMoveBase::calc_();
}

}  // namespace uking::action
