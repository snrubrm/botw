#include "aal/aalSpeakerBalanceUnifierArea.h"
#include <basis/seadNew.h>
#include <cfloat>
#include <math/seadMathCalcCommon.h>
#include "aal/aalMeter.h"

namespace aal {

// 0x7100b935d8
SpeakerBalanceUnifierArea::SpeakerBalanceUnifierArea() {
    mAttenuator = nullptr;
    mRegisterCullingDistanceSquared = FLT_MAX;
    for (s32 i = 0; i < cSegmentNum; ++i)
        mSegments[i] = nullptr;
    mInteriorNum = 0;
    mSpread = 0.0f;
    _214 = false;
}

// 0x7100b93618
SpeakerBalanceUnifierArea::~SpeakerBalanceUnifierArea() = default;

// 0x7100b9361c
void SpeakerBalanceUnifierArea::initialize(sead::Heap* heap) {
    for (s32 i = 0; i < cSegmentNum; ++i)
        mSegments[i] = new (heap, 0x20) SpeakerBalanceUnifierAreaSegment;
    reset();
}

// 0x7100b93688
void SpeakerBalanceUnifierArea::reset() {
    for (s32 i = 0; i < cSegmentNum; ++i)
        mSegments[i]->reset();
}

// 0x7100b936bc
void SpeakerBalanceUnifierArea::finalize() {
    for (s32 i = 0; i < cSegmentNum; ++i) {
        if (mSegments[i]) {
            delete mSegments[i];
            mSegments[i] = nullptr;
        }
    }
}

// 0x7100b936f8
void SpeakerBalanceUnifierArea::initParams() {
    mAttenuator = nullptr;
    mRegisterCullingDistanceSquared = FLT_MAX;
    mInteriorNum = 0;
    mSpread = 0.0f;
    _214 = false;
}

// 0x7100b93714
bool SpeakerBalanceUnifierArea::registerPosition(const sead::Vector3f& position,
                                                 const sead::Vector3f& direction) {
    const f32 squared_distance = position.x * position.x + position.y * position.y + position.z * position.z;
    if (squared_distance >= mRegisterCullingDistanceSquared)
        return false;
    const u32 angle_idx = sead::MathCalcCommon<f32>::atan2Idx(direction.z, direction.x);
    SpeakerBalanceUnifierAreaSegment* segment = mSegments[(angle_idx + 0x40000000) >> 26];
    if (!segment->setSquaredDistanceIfNear(squared_distance))
        return false;
    segment->mPosition = position;
    segment->mSquaredDistance = position.x * position.x + position.z * position.z;
    return true;
}

// 0x7100b93d04
void SpeakerBalanceUnifierArea::setAttenuator(Attenuator* attenuator) {
    mAttenuator = attenuator;
}

// 0x7100b93e70
void SpeakerBalanceUnifierArea::setRegisterCullingDistance(f32 distance) {
    if (distance == 0.0f)
        mRegisterCullingDistanceSquared = FLT_MAX;
    else {
        const f32 length = Meter::toLength(distance);
        mRegisterCullingDistanceSquared = length * length;
    }
}

// 0x7100b93eac
void SpeakerBalanceUnifierArea::setInteriorNum(s32 num) {
    if (num >= 0)
        mInteriorNum = num;
}

// 0x7100b93eb8
void SpeakerBalanceUnifierArea::setSpread(f32 spread) {
    mSpread = spread;
}
}  // namespace aal
