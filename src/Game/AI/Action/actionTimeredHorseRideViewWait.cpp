#include "Game/AI/Action/actionTimeredHorseRideViewWait.h"
#include "KingSystem/System/Timer.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

TimeredHorseRideViewWait::TimeredHorseRideViewWait(const InitArg& arg) : HorseRideViewWait(arg) {}

TimeredHorseRideViewWait::~TimeredHorseRideViewWait() = default;

bool TimeredHorseRideViewWait::init_(sead::Heap* heap) {
    return HorseRideViewWait::init_(heap);
}

// NON_MATCHING: the original loads both params before fetching the GlobalRandom instance
void TimeredHorseRideViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideViewWait::enter_(params);
    _60 = *mTime_s + s32(sead::GlobalRandom::instance()->getU32(*mTimeRand_s));
}

void TimeredHorseRideViewWait::leave_() {
    HorseRideViewWait::leave_();
}

void TimeredHorseRideViewWait::loadParams_() {
    HorseRideViewWait::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void TimeredHorseRideViewWait::calc_() {
    HorseRideViewWait::calc_();
    ksys::Timer::update(&_60, -1.0f);
    if (_60 <= 0.0f)
        setFinished();
}

}  // namespace uking::action
