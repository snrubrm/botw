#include "Game/AI/Action/actionForkTimerBase.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

ForkTimerBase::ForkTimerBase(const InitArg& arg) : Fork(arg) {}

ForkTimerBase::~ForkTimerBase() = default;

bool ForkTimerBase::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkTimerBase::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    const int time = m32();
    if (time > 0) {
        _30 = time;
        return;
    }
    _30 = 0.0f;
    setEndState();
}

void ForkTimerBase::leave_() {
    Fork::leave_();
}

void ForkTimerBase::loadParams_() {
    Fork::loadParams_();
}

void ForkTimerBase::calc_() {
    Fork::calc_();
    if (_30 > 0.0f) {
        ksys::Timer::update(&_30, -m33());
        if (_30 <= 0.0f)
            setEndState();
    }
}

int ForkTimerBase::m32() {
    return 0;
}

float ForkTimerBase::m33() {
    return 1.0f;
}

}  // namespace uking::action
