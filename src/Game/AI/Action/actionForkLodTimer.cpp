#include "Game/AI/Action/actionForkLodTimer.h"

namespace uking::action {

ForkLodTimer::ForkLodTimer(const InitArg& arg) : Fork(arg) {}

ForkLodTimer::~ForkLodTimer() = default;

bool ForkLodTimer::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkLodTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    if (*mWaitFrame_s > 0) {
        _38.mTimer.reset(*mWaitFrame_s);
    } else {
        _38.mTimer = ksys::Timer(-1.0f, -1.0f, 0.0f);
        setEndState();
    }
}

void ForkLodTimer::leave_() {
    Fork::leave_();
}

void ForkLodTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
}

void ForkLodTimer::calc_() {
    Fork::calc_();
    if (_38.mTimer.value <= sead::Mathf::epsilon())
        return;

    _38.sub_7100D3BCE4();
    if (_38.mTimer.value <= sead::Mathf::epsilon())
        setEndState();
}

}  // namespace uking::action
