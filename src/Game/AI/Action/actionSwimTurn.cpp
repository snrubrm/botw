#include "Game/AI/Action/actionSwimTurn.h"

namespace uking::action {

SwimTurn::SwimTurn(const InitArg& arg) : SwimTurnBase(arg) {}

SwimTurn::~SwimTurn() = default;

bool SwimTurn::init_(sead::Heap* heap) {
    return SwimTurnBase::init_(heap);
}

void SwimTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimTurnBase::enter_(params);
    if (mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void SwimTurn::leave_() {
    SwimTurnBase::leave_();
}

void SwimTurn::loadParams_() {
    SwimTurnBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void SwimTurn::calc_() {
    SwimTurnBase::calc_();
}

}  // namespace uking::action
