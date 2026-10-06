#include "aal/aalFxDelayParamSetter.h"

namespace aal {

// 0x71012cbdd8
FxDelayParamSetter::FxDelayParamSetter() {
    reset();
}

// 0x71012cbe2c
void FxDelayParamSetter::resetImpl_() {
    mDelay = 0.1f;
    mFeedback = 0.4f;
    mOutGain = 1.0f;
    mLpf = 1.0f;
}

// 0x71012cbe50
void FxDelayParamSetter::setDelay(f32 delay) {
    mDelay = delay;
    setModifiedFlagBit_(0);
}

// 0x71012cbe5c
void FxDelayParamSetter::setFeedback(f32 feedback) {
    mFeedback = feedback;
    setModifiedFlagBit_(1);
}

// 0x71012cbe68
void FxDelayParamSetter::setOutGain(f32 gain, f32 gain2) {
    mOutGain = gain;
    mOutGain2 = gain2;
    setModifiedFlagBit_(2);
}

// 0x71012cbe78
void FxDelayParamSetter::setLpf(f32 lpf) {
    mLpf = lpf;
    setModifiedFlagBit_(3);
}

}  // namespace aal
