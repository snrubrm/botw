#include "Game/AI/Action/actionTimeredNeckSpin.h"

namespace uking::action {

TimeredNeckSpin::TimeredNeckSpin(const InitArg& arg) : NeckSpin(arg) {}

TimeredNeckSpin::~TimeredNeckSpin() = default;

void TimeredNeckSpin::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpin::enter_(params);
    const f32 time = f32(*mParams.mTime_s);
    _8c.rate = -1.0f;
    _8c.value = time;
    _8c.previous_value = time;
    const f32 speed = *mParams.mInitSpinSpeed_s / 30.0f;
    _80.value = speed;
    _80.prev_value = speed;
}

void TimeredNeckSpin::leave_() {
    NeckSpin::leave_();
}

void TimeredNeckSpin::loadParams_() {
    NeckSpin::loadParams_();
    getStaticParam(&mParams.mTime_s, "Time");
    getStaticParam(&mParams.mSpinSpeedRatio_s, "SpinSpeedRatio");
    getStaticParam(&mParams.mInitSpinSpeed_s, "InitSpinSpeed");
}

void TimeredNeckSpin::calc_() {
    const f32 target = *mSpinSpeed_s / 30.0f;
    _80.lerp(target, *mParams.mSpinSpeedRatio_s);
    _80.updateStats();
    NeckSpin::calc_();
    _8c.update();
    if (_8c.value <= sead::Mathf::epsilon())
        setFinished();
}

}  // namespace uking::action
