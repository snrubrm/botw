#include "Game/AI/Action/actionWaterFloatWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

WaterFloatWait::WaterFloatWait(const InitArg& arg) : WaterFloatImmobile(arg) {}

bool WaterFloatWait::init_(sead::Heap* heap) {
    return WaterFloatImmobile::init_(heap);
}

void WaterFloatWait::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterFloatImmobile::enter_(params);
    const f32 time = f32(*mTime_s) + f32(*mTimeRand_s) * sead::GlobalRandom::instance()->getF32();
    _a0 = ksys::Timer(time, time);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), *mIsIgnoreSameAS_s, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
}

void WaterFloatWait::leave_() {
    WaterFloatImmobile::leave_();
}

void WaterFloatWait::loadParams_() {
    WaterFloatImmobile::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mIsEndWhenASFinished_s, "IsEndWhenASFinished");
    getStaticParam(&mASName_s, "ASName");
}

void WaterFloatWait::calc_() {
    WaterFloatImmobile::calc_();
    if (*mIsEndWhenASFinished_s && mActor->getASList()->x_4(0, 0)) {
        setFinished();
        return;
    }
    if (*mTime_s < 1)
        return;
    if (_a0.value <= sead::Mathf::epsilon())
        setFinished();
    else
        _a0.update();
}

}  // namespace uking::action
