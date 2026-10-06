#include "aal/aalSoundParam.h"
#include <math/seadMathCalcCommon.h>
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

// 0x7100b764ec
void SoundParam::aggregate(SoundParam* dst, const SoundParam& src) {
    dst->mVolume = src.mVolume * dst->mVolume;
    for (s32 i = 0; i < 1; ++i) {
        if (src.mDeviceVolume[i] >= 0.0f)
            dst->mDeviceVolume[i] = dst->mDeviceVolume[i] < 0.0f ? src.mDeviceVolume[i]
                                                                  : src.mDeviceVolume[i] * dst->mDeviceVolume[i];
    }
    for (s32 i = 0; i < 4; ++i) {
        if (src.mBusVolume[i] >= 0.0f)
            dst->mBusVolume[i] = dst->mBusVolume[i] < 0.0f ? src.mBusVolume[i] : src.mBusVolume[i] * dst->mBusVolume[i];
    }
    dst->mPitch = src.mPitch * dst->mPitch;
    dst->mLfe = src.mLfe + dst->mLfe;
    dst->mLpf = src.mLpf + dst->mLpf;
    if (dst->mBiquadType < 0)
        dst->mBiquadType = src.mBiquadType;
    dst->mBiquadValue = src.mBiquadValue + dst->mBiquadValue;
    dst->mAngleIdx = src.mAngleIdx + dst->mAngleIdx;
    dst->mSpread = src.mSpread + dst->mSpread;
}

// NON_MATCHING: the same results; the original keeps branches in the volume merge where this uses conditional selects.
// 0x7100b7660c
void SoundParam::aggregate(SoundParam* dst, const SoundParam& src1, const SoundParam& src2) {
    dst->mVolume = src1.mVolume * src2.mVolume;
    for (s32 i = 0; i < 1; ++i) {
        f32 volume = src1.mDeviceVolume[i];
        if (src2.mDeviceVolume[i] >= 0.0f)
            volume = volume < 0.0f ? src2.mDeviceVolume[i] : src2.mDeviceVolume[i] * volume;
        dst->mDeviceVolume[i] = volume;
    }
    for (s32 i = 0; i < 4; ++i) {
        f32 volume = src1.mBusVolume[i];
        if (src2.mBusVolume[i] >= 0.0f)
            volume = volume < 0.0f ? src2.mBusVolume[i] : src2.mBusVolume[i] * volume;
        dst->mBusVolume[i] = volume;
    }
    dst->mPitch = src1.mPitch * src2.mPitch;
    dst->mLfe = src1.mLfe + src2.mLfe;
    dst->mLpf = src1.mLpf + src2.mLpf;
    dst->mBiquadType = src2.mBiquadType < 0 ? src1.mBiquadType : src2.mBiquadType;
    dst->mBiquadValue = src1.mBiquadValue + src2.mBiquadValue;
    dst->mAngleIdx = src2.mAngleIdx + src1.mAngleIdx;
    dst->mSpread = src1.mSpread + src2.mSpread;
}

// NON_MATCHING: the same comparison; the static initial parameters and their guard are laid out in the other order.
// 0x7100b76758
bool SoundParam::isInitial(const SoundParam& param) {
    static SoundParam sInitialParam;
    return std::memcmp(&param, &sInitialParam, sizeof(SoundParam)) == 0;
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

// 0x7100b76364
void SoundParam::setDeviceVolume(DeviceType device, f32 volume) {
    mDeviceVolume[device] = volume;
}

// 0x7100b76380
void SoundParam::setBusVolume(BusType bus, f32 volume) {
    mBusVolume[bus] = volume;
}

// 0x7100b763d8: NON_MATCHING (the original converts through a signed 64-bit register: fcvtzs x8)
void SoundParam::setAngle(f32 angle) {
    mAngleIdx = sead::Mathf::rad2idx(angle);
}

// 0x7100b764bc
void SoundParam::clampMinBusVolume() {
    for (f32& volume : mBusVolume)
        volume = sead::Mathf::clampMin(volume, 0.0f);
}

// 0x7100b76400
void SoundParam::clampExceptVolume() {
    mPitch = sead::Mathf::clampMin(mPitch, 0.0f);
    mLfe = sead::Mathf::clamp(mLfe, 0.0f, 2.0f);
    if (mBiquadType < 0)
        mBiquadType = 3;
    mLpf = sead::Mathf::clamp(mLpf, 0.0f, 1.0f);
    mBiquadValue = sead::Mathf::clamp(mBiquadValue, 0.0f, 1.0f);
    mSpread = sead::Mathf::clamp(mSpread, -1.0f, 1.0f);
}

}  // namespace aal
