#include "Game/AI/Action/actionEventPlayMovieAction.h"

namespace uking::action {

EventPlayMovieAction::EventPlayMovieAction(const InitArg& arg) : ksys::act::ai::Action(arg) {
    // NON_MATCHING: our build materialises the _70 u64 with one redundant movk #0 (16-bit-repeating
    // bitmask + patch) where the original uses the 32-bit-repeating bitmask + patch (2 insns).
    // All stores, branches, calls and other constants are identical.
    _38.copy("Skip A !");
    _70 = 0x43ed3fc03fc00000;
    _78 = 0xc3960000;
    _80 = 0x42480000434e0000;
}

EventPlayMovieAction::~EventPlayMovieAction() = default;

bool EventPlayMovieAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayMovieAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayMovieAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayMovieAction::loadParams_() {
    getDynamicParam(&mFileName_d, "FileName");
}

void EventPlayMovieAction::calc_() {
    if (!isFinished() && !isFailed()) {
        setFinished();
        mFlags.set(Flag::Changeable);
    }
}

}  // namespace uking::action
