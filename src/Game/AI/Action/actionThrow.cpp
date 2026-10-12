#include "Game/AI/Action/actionThrow.h"

namespace uking::action {

Throw::Throw(const InitArg& arg) : StopBase(arg) {}

bool Throw::init_(sead::Heap* heap) {
    return _30.init(heap);
}

void Throw::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
    m32();
    mFlags.reset(Flag::Changeable);
    _30.enter(params);
}

void Throw::leave_() {
    StopBase::leave_();
}

void Throw::loadParams_() {
    StopBase::loadParams_();
    _30.loadParams();
}

void Throw::calc_() {
    StopBase::calc_();
    _30.calc();
    if (isFinishedAS(0, 0))
        setFinished();
}

void Throw::m32() {
    playAS("Throw", false, 0, 0, -1.0f);
}

}  // namespace uking::action
