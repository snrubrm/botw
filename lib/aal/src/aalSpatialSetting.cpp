#include "aal/aalSpatialSetting.h"
#include "aal/aalAttenuationMgr.h"
#include "aal/aalMeter.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b91744
SpatialSetting::SpatialSetting() {
    reset();
}

// 0x7100b917e8
void SpatialSetting::reset() {
    mActorMatrix = sead::Matrix34f::zero;
    mVelocity = sead::Vector3f::zero;
    mPositioned = true;
    mPositionFollow = true;
    mExclusiveCalculator = 0;
    mSetting.initialize();
    mSetting.actor_matrix = &mActorMatrix;
    mSetting.velocity = &mVelocity;
}

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
    mSetting.actor_matrix = &mActorMatrix;
}

// 0x7100b918a0
void SpatialSetting::setVelocity(const sead::Vector3f& velocity) {
    mVelocity = velocity;
    mSetting.velocity = &mVelocity;
}

// 0x7100b919d0
void SpatialSetting::getPosition(sead::Vector3f* position) const {
    if (position)
        mActorMatrix.getTranslation(*position);
}

// 0x7100b919f0
void SpatialSetting::setAttenuator(const sead::SafeString& name) {
    if (AttenuationMgr* mgr = SystemAccessor::getAttenuationMgr()) {
        if (Attenuator* attenuator = mgr->findAttenuatorOrDefault(name))
            mSetting.attenuator = attenuator;
    }
}

// 0x7100b91a28
void SpatialSetting::setDopplerFactor(f32 factor) {
    mSetting.doppler_factor = factor;
}

// 0x7100b91a30
void SpatialSetting::setSoundSourceSize(f32 size) {
    if (size >= 0.0f)
        mSetting.sound_source_size = Meter::toLength(size);
}

// 0x7100b91a5c
void SpatialSetting::setUseSoundSourceSizeForAttenuation(bool enable) {
    mSetting.flags = enable ? mSetting.flags | 4 : mSetting.flags & ~4;
}

// 0x7100b91a7c
void SpatialSetting::setRotatingStereoEnabled(bool enable) {
    mSetting.flags = enable ? mSetting.flags | 0x10 : mSetting.flags & ~0x10;
}

// 0x7100b91a9c
void SpatialSetting::setListenerDirectivityEnabled(bool enable) {
    mSetting.flags = enable ? mSetting.flags | 0x20 : mSetting.flags & ~0x20;
}

// 0x7100b91abc
void SpatialSetting::setShape(Shape* shape) {
    mSetting.shape = shape;
}

// 0x7100b91ac4
void SpatialSetting::setUnified(bool unified) {
    mSetting.flags = unified ? mSetting.flags | 2 : mSetting.flags & ~2;
}

// 0x7100b91aec
void SpatialSetting::setSpatialCalculatorSetting(const SpatialCalculator::Setting& setting) {
    mSetting = setting;
}

// 0x7100b91ae4
void SpatialSetting::setUserParam(u64 param) {
    mSetting.user_param = param;
}

}  // namespace aal
