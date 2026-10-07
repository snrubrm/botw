#include "Game/AI/AI/aiTimeredViewWait.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

TimeredViewWait::TimeredViewWait(const InitArg& arg) : ViewWait(arg) {}

TimeredViewWait::~TimeredViewWait() = default;

bool TimeredViewWait::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void TimeredViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
    const s32 time = *mTime_s;
    const s32 rand_time = *mTimeRand_s;
    _70 = time + s32(sead::GlobalRandom::instance()->getU32(rand_time));
}

void TimeredViewWait::calc_() {
    ViewWait::calc_();
    ksys::Timer::update(&_70, -1.0f);
    if (_70 <= 0 && isChangeable())
        setFinished();
}

void TimeredViewWait::leave_() {
    ViewWait::leave_();
}

void TimeredViewWait::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

}  // namespace uking::ai
