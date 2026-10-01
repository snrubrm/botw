#include "Game/AI/AI/aiTimedGuardNearTarget.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"

namespace uking::ai {

TimedGuardNearTarget::TimedGuardNearTarget(const InitArg& arg) : GuardNearTarget(arg) {}

TimedGuardNearTarget::~TimedGuardNearTarget() = default;

bool TimedGuardNearTarget::init_(sead::Heap* heap) {
    return GuardNearTarget::init_(heap);
}

void TimedGuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const int time = *mGuardEndTime_s;
    _a4 = time;
    _a8 = time;
    _a0 = time;
    GuardNearTarget::enter_(params);
}

void TimedGuardNearTarget::calc_() {
    f32& timer = _a0;
    if (m39(sub_710044C9E8())) {
        ksys::Timer::update(&timer, -1.0f);
    } else {
        s32 time = _a4;
        if (_a8 != _a4)
            time = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
        timer = time;
    }
    GuardNearTarget::calc_();
}

void TimedGuardNearTarget::leave_() {
    GuardNearTarget::leave_();
}

void TimedGuardNearTarget::loadParams_() {
    GuardNearTarget::loadParams_();
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mGuardStartAngle_s, "GuardStartAngle");
    getStaticParam(&mGuardEndAngle_s, "GuardEndAngle");
}

bool TimedGuardNearTarget::m36(float distance) {
    return _a0 <= 0.0f;
}

}  // namespace uking::ai
