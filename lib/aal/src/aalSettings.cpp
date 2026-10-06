#include "aal/aalSettings.h"

namespace aal {

// 0x7100ba104c
void Settings::setBaseFPS(f32 fps) {
    if (fps > 0.0f) {
        mSoundDistancePerFrame = mSoundSpeed * mLengthPerMeter / fps;
        mBaseFPS = fps;
        mCalcTimeStep = mFrameWaitIntervalStepRate / fps;
    }
}

// 0x7100ba107c
void Settings::setFrameWaitIntervalStepRate(f32 rate) {
    if (rate > 0.0f) {
        mFrameWaitIntervalStepRate = rate;
        mCalcTimeStep = rate / mBaseFPS;
    }
}

// 0x7100ba1094
void Settings::setLengthPerMeter(f32 length) {
    if (length > 0.0f) {
        mLengthPerMeter = length;
        mLengthPerMeterSquared = length * length;
        mSoundDistancePerFrame = mSoundSpeed * length / mBaseFPS;
    }
}

// 0x7100ba10bc
f32 Settings::getDopplerPitchMin() const {
    return mDopplerMode == 1 ? 1.0f : mDopplerPitchMin;
}

// 0x7100ba10d8
f32 Settings::getDopplerPitchMax() const {
    return mDopplerMode == 1 ? 1.0f : mDopplerPitchMax;
}

}  // namespace aal
