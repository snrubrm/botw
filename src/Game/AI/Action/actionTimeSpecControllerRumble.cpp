#include "Game/AI/Action/actionTimeSpecControllerRumble.h"
#include "Game/gameRumble.h"

namespace uking::action {

TimeSpecControllerRumble::TimeSpecControllerRumble(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

TimeSpecControllerRumble::~TimeSpecControllerRumble() = default;

bool TimeSpecControllerRumble::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling only (the `3 + (pattern == 1)` constant is materialised before the compare)
void TimeSpecControllerRumble::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* rumble = Rumble::instance()) {
        const int pattern = *mPattern_s;
        rumble->sub_710089813C(pattern == 2 ? 5 : 3 + (pattern == 1), *mSeconds_d);
        _38.setNow();
    }
}

void TimeSpecControllerRumble::leave_() {
    ksys::act::ai::Action::leave_();
}

void TimeSpecControllerRumble::loadParams_() {
    getStaticParam(&mPattern_s, "Pattern");
    getDynamicParam(&mSeconds_d, "Seconds");
    getDynamicParam(&mIsWait_d, "IsWait");
}

void TimeSpecControllerRumble::calc_() {
    if (*mIsWait_d) {
        if (*mSeconds_d > _38.diffToNow().toSeconds())
            return;

        if (auto* rumble = Rumble::instance())
            rumble->sub_710089878C();
    }

    setFinished();
}

}  // namespace uking::action
