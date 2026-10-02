#include "Game/AI/Action/actionHorseRideWait.h"
#include "math/seadMathCalcCommon.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

HorseRideWait::HorseRideWait(const InitArg& arg) : HorseRide(arg) {}

HorseRideWait::~HorseRideWait() = default;

bool HorseRideWait::init_(sead::Heap* heap) {
    return HorseRide::init_(heap);
}

// NON_MATCHING: load scheduling around the GlobalRandom instance load (same as WaitBase::enter_)
void HorseRideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRide::enter_(params);
    mFlags.set(Flag::Changeable);
    const f32 time = *mTime_s + s32(sead::GlobalRandom::instance()->getU32(*mTimeRand_s));
    _40 = ksys::Timer(time, time);
    sub_71001AD8A0("HorseWait", true);
}

void HorseRideWait::leave_() {
    HorseRide::leave_();
}

void HorseRideWait::loadParams_() {
    HorseRide::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void HorseRideWait::calc_() {
    HorseRide::calc_();
    if (*mTime_s < 1)
        return;
    if (_40.value <= sead::Mathf::epsilon())
        setFinished();
    else
        _40.update();
}

}  // namespace uking::action
