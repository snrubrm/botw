#include "aal/aalSpatialSetting.h"
#include "aal/aalMeter.h"

namespace aal {

// 0x7100b91860 / 0x7100b91864
SpatialSetting::~SpatialSetting() = default;

// 0x7100b91868
void SpatialSetting::setPositioned(bool positioned) {
    mPositioned = positioned;
}

// 0x7100b91874
void SpatialSetting::setPositionFollow(bool follow) {
    mPositionFollow = follow;
}

// 0x7100b91880
void SpatialSetting::setActorMatrix(const sead::Matrix34f& matrix) {
    mActorMatrix = matrix;
    _48 = &mActorMatrix;
}

// 0x7100b918a0
void SpatialSetting::setVelocity(const sead::Vector3f& velocity) {
    mVelocity = velocity;
    _50 = &mVelocity;
}

// 0x7100b919d0
void SpatialSetting::getPosition(sead::Vector3f* position) const {
    if (position)
        mActorMatrix.getTranslation(*position);
}

// 0x7100b91a28
void SpatialSetting::setDopplerFactor(f32 factor) {
    mDopplerFactor = factor;
}

// 0x7100b91a30
void SpatialSetting::setSoundSourceSize(f32 size) {
    if (size >= 0.0f)
        mSoundSourceSize = Meter::toLength(size);
}

// 0x7100b91a5c
void SpatialSetting::setUseSoundSourceSizeForAttenuation(bool enable) {
    mFlags = enable ? mFlags | 4 : mFlags & ~4;
}

// 0x7100b91a7c
void SpatialSetting::setRotatingStereoEnabled(bool enable) {
    mFlags = enable ? mFlags | 0x10 : mFlags & ~0x10;
}

// 0x7100b91a9c
void SpatialSetting::setListenerDirectivityEnabled(bool enable) {
    mFlags = enable ? mFlags | 0x20 : mFlags & ~0x20;
}

// 0x7100b91abc
void SpatialSetting::setShape(Shape* shape) {
    mShape = shape;
}

// 0x7100b91ac4
void SpatialSetting::setUnified(bool unified) {
    mFlags = unified ? mFlags | 2 : mFlags & ~2;
}

// 0x7100b91ae4
void SpatialSetting::setUserParam(u64 param) {
    mUserParam = param;
}

}  // namespace aal
