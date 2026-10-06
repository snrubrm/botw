#include "aal/aalSoundSource.h"

namespace aal {

// 0x7100b77d6c
void SoundSource::pause(bool pause, f32 fade_time) {
    this->pause(sead::BitFlag8(0xff), pause, fade_time);
}

// NON_MATCHING: the original sets the result to false up front and loads mState before the sign test
// 0x7100b77e8c
bool SoundSource::setStartDelayTime(f32 delay_time) {
    bool result = false;
    if (delay_time >= 0.0f && mState <= 2) {
        mStartDelayTime = delay_time;
        mState = delay_time > 0.0f ? 1 : 2;
        result = true;
    }
    return result;
}

// NON_MATCHING: same shape as setStartDelayTime (result initialised up front, mState loaded first)
// 0x7100b77ec4
bool SoundSource::setFadeInTime(f32 fade_in_time) {
    bool result = false;
    if (fade_in_time >= 0.0f && mState <= 2) {
        mFadeInTime = fade_in_time;
        result = true;
    }
    return result;
}

// 0x7100b781c0
bool SoundSource::isVirtualized() const {
    return mVirtualizedBy != 0;
}

}  // namespace aal
