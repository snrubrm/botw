#include "Game/AI/Action/actionTimeredHorseRideViewWait.h"
#include "KingSystem/System/Timer.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

TimeredHorseRideViewWait::TimeredHorseRideViewWait(const InitArg& arg) : HorseRideViewWait(arg) {}

TimeredHorseRideViewWait::~TimeredHorseRideViewWait() = default;

bool TimeredHorseRideViewWait::init_(sead::Heap* heap) {
    return HorseRideViewWait::init_(heap);
}

void TimeredHorseRideViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideViewWait::enter_(params);
    const s32 time = *mTime_s;
    const u32 rand = *mTimeRand_s;
    _60 = time + s32(sead::GlobalRandom::instance()->getU32(rand));
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
