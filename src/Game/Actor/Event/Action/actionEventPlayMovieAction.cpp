#include "Game/Actor/Event/Action/actionEventPlayMovieAction.h"

namespace uking::action {

EventPlayMovieAction::EventPlayMovieAction(const InitArg& arg) : ksys::act::ai::Action(arg) {
    _38.copy("Skip A !");
    _70 = 0x43ed00003fc00000;
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
