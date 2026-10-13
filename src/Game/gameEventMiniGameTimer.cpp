#include "Game/gameEventMgrMiniGame.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/VFR.h"

Unk_71024e8128::Unk_71024e8128() = default;

void Unk_71024e8128::reset() {
    mTimer.value = mTimer.previous_value = 0.0f;
    mInitialTime = 0.0f;
    mMode = 0;
}

// NON_MATCHING: initial time and mode use a paired store instead of a combined constant.
void Unk_71024e8128::startCountup(s32 max_time_ms) {
    mTimer.reset(0.0f, 1.0f);
    mMaxTimeMs = sead::Mathi::clamp(max_time_ms, 0, 5999999);
    mInitialTime = 0.0f;
    mMode = 1;
}

void Unk_71024e8128::startCountdown(s32 start_time_ms) {
    mMaxTimeMs = 5999999;
    mTimer.reset(static_cast<f32>(sead::Mathi::clamp(start_time_ms, 0, mMaxTimeMs) /
                                 (1000 / ksys::VFR::instance()->getFrameRate())), -1.0f);
    mInitialTime = mTimer.value;
    mMode = 1;
}

// NON_MATCHING: time conversion registers and the maximum-time load scheduling differ.
s32 Unk_71024e8128::getTimerMs() const {
    const s32 milliseconds = (1000 / ksys::VFR::instance()->getFrameRate()) *
                            static_cast<s32>(mTimer.value);
    return milliseconds > mMaxTimeMs ? mMaxTimeMs : milliseconds;
}

// NON_MATCHING: inlined time conversion registers and load scheduling differ.
void Unk_71024e8128::sub_7100E499EC() {
    if (mMode != 1)
        return;
    mTimer.update();
    if (mTimer.value <= sead::Mathf::epsilon()) {
        mTimer.value = mTimer.previous_value = 0.0f;
        mMode = 2;
    } else if (getTimerMs() % 1000 > mMaxTimeMs) {
        mMode = 2;
    }
}
