#include "aal/aalSoundParam.h"
#include <cstring>

namespace aal {

// 0x7100b762cc
SoundParam::SoundParam() {
    reset();
}

// 0x7100b76334
SoundParam::SoundParam(const SoundParam& other) {
    copy(this, other);
}

// 0x7100b767fc / 0x7100b76800
SoundParam::~SoundParam() = default;

// 0x7100b76308
void SoundParam::reset() {
    mPitch = 1.0f;
    mLfe = 0.0f;
    mLpf = 0.0f;
    mBiquadType = -1;
    mBiquadValue = 0.0f;
    mVolume = 1.0f;
    mDeviceVolume[0] = -1.0f;
    for (auto& volume : mBusVolume)
        volume = -1.0f;
    mAngleIdx = 0;
    mSpread = 0.0f;
}

// 0x7100b7634c
void SoundParam::copy(SoundParam* dst, const SoundParam& src) {
    std::memcpy(dst, &src, sizeof(SoundParam));
}

// 0x7100b76354
void SoundParam::setVolume(f32 volume) {
    if (volume >= 0.0f)
        mVolume = volume;
}

// 0x7100b7639c
void SoundParam::setPitch(f32 pitch) {
    if (pitch >= 0.0f)
        mPitch = pitch;
}

// 0x7100b763ac
void SoundParam::setLfe(f32 lfe) {
    mLfe = lfe;
}

// 0x7100b763b4
void SoundParam::setLpf(f32 lpf) {
    mLpf = lpf;
}

// 0x7100b763bc
void SoundParam::setBiquadFilter(int type, f32 value) {
    mBiquadType = type;
    mBiquadValue = value;
}

// 0x7100b763c8
void SoundParam::setBiquadType(int type) {
    mBiquadType = type;
}

// 0x7100b763d0
void SoundParam::setBiquadValue(f32 value) {
    mBiquadValue = value;
}

// 0x7100b763f0
void SoundParam::setAngleIdx(u32 index) {
    mAngleIdx = index;
}

// 0x7100b763f8
void SoundParam::setSpread(f32 spread) {
    mSpread = spread;
}

}  // namespace aal
