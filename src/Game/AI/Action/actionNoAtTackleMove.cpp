#include "Game/AI/Action/actionNoAtTackleMove.h"

namespace uking::action {

NoAtTackleMove::NoAtTackleMove(const InitArg& arg) : TackleMove(arg) {}

NoAtTackleMove::~NoAtTackleMove() = default;

bool NoAtTackleMove::init_(sead::Heap* heap) {
    return TackleMove::init_(heap);
}

void NoAtTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    TackleMove::enter_(params);
    playAS(mAS_s.cstr(), true, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
}

void NoAtTackleMove::leave_() {
    TackleMove::leave_();
}

void NoAtTackleMove::loadParams_() {
    TackleMove::loadParams_();
    getStaticParam(&mAS_s, "AS");
}

void NoAtTackleMove::calc_() {
    TackleMove::calc_();
}

void NoAtTackleMove::m33() {
    setFinished();
}

}  // namespace uking::action
