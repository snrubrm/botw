#include "Game/AI/Action/actionEventWaitFrameAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

EventWaitFrameAction::EventWaitFrameAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventWaitFrameAction::~EventWaitFrameAction() = default;

bool EventWaitFrameAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventWaitFrameAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = *mFrame_d;
}

void EventWaitFrameAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventWaitFrameAction::loadParams_() {
    getDynamicParam(&mFrame_d, "Frame");
}

void EventWaitFrameAction::calc_() {
    if (isFinished() || isFailed())
        return;
    ksys::Timer::update(&_28, -1.0f);
    if (_28 <= 0.0f) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
