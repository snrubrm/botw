#include "Game/AI/Action/actionWaitTimer.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

WaitTimer::WaitTimer(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitTimer::~WaitTimer() = default;

bool WaitTimer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = *mWaitFrame_s;
    mFlags.set(Flag::Changeable);
}

bool WaitTimer::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::Action::reenter_(other, true))
        return false;
    auto* other_ = sead::DynamicCast<WaitTimer>(other);
    if (!other_)
        return false;
    _28 = other_->_28;
    return true;
}

void WaitTimer::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitTimer::loadParams_() {
    getStaticParam(&mWaitFrame_s, "WaitFrame");
}

void WaitTimer::calc_() {
    ksys::Timer::update(&_28, -1.0f);
    if (_28 <= 0.0f)
        setFinished();
}

}  // namespace uking::action
