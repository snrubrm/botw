#include "Game/AI/Action/actionOneTimeStopASPlayerNoEnd.h"

namespace uking::action {

OneTimeStopASPlayerNoEnd::OneTimeStopASPlayerNoEnd(const InitArg& arg) : StopASPlay(arg) {}

OneTimeStopASPlayerNoEnd::~OneTimeStopASPlayerNoEnd() = default;

bool OneTimeStopASPlayerNoEnd::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void OneTimeStopASPlayerNoEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
    mFlags.reset(Flag::Changeable);
}

void OneTimeStopASPlayerNoEnd::leave_() {
    StopASPlay::leave_();
}

void OneTimeStopASPlayerNoEnd::loadParams_() {
    StopASPlay::loadParams_();
}

void OneTimeStopASPlayerNoEnd::calc_() {
    StopASPlay::calc_();
    if (isFinishedAS(0, 0))
        mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
