#include "Game/AI/Action/actionWaitBase.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

WaitBase::WaitBase(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

void WaitBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    const s32 base_time = *mTime_s;
    const u32 rand_time = *mTimeRand_s;
    const f32 time = base_time + s32(sead::GlobalRandom::instance()->getU32(rand_time));
    mTimer = ksys::Timer(time, time);
    mFlags.set(Flag::Changeable);
}

void WaitBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
}

void WaitBase::calc_() {
    ActionWithPosAngReduce::calc_();
    if (*mTime_s < 1)
        return;
    if (mTimer.value <= sead::Mathf::epsilon()) {
        setFinished();
        return;
    }
    mTimer.update();
}

}  // namespace uking::action
