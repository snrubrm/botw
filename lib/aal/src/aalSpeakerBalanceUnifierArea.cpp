#include "aal/aalSpeakerBalanceUnifierArea.h"
#include <basis/seadNew.h>
#include <cfloat>
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "aal/aalAttenuationCulling.h"
#include "aal/aalAttenuationMgr.h"
#include "aal/aalAttenuator.h"
#include "aal/aalInterior.h"
#include "aal/aalInteriorSet.h"
#include "aal/aalListener.h"
#include "aal/aalMeter.h"
#include "aal/aalOutputDevice.h"
#include "aal/aalSettings.h"
#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// NON_MATCHING: native frame allocation, register use and branch joins differ.
void SpeakerBalanceUnifierArea::calcSpeakerBalance(
    sead::Buffer<SpeakerChannelVolume>* volumes, f32* parameter, f32* filter,
    f32* priority_factor, const Listener& listener, s32 device_num, f32* max_gain) {
    SpeakerBalanceUnifierMgr* mgr = SystemAccessor::getSpeakerBalanceUnifierMgr();
    UnifierSpeakerBalanceTable* table = mgr->getTable();
    if (!mAttenuator)
        mAttenuator = SystemAccessor::getAttenuationMgr()->getDefaultAttenuator();
    Curve* volume_curve = mAttenuator ? mAttenuator->getCurve(DistanceParamTarget::Volume) : nullptr;
    Curve* spread_curve = mAttenuator ? mAttenuator->getCurve(DistanceParamTarget::Spread) : nullptr;
    if (max_gain)
        *max_gain = 0.0f;

    s32 interior_num = 0;
    f32 interior_spread = 0.0f;
    for (s32 i = 0; i < device_num; ++i) {
        const DeviceType device(i);
        interior_num = mInteriorNum < table->getCurrentInteriorNum(device) ? mInteriorNum : 0;
        OutputDevice* output_device = SystemAccessor::getSettings()->getOutputDevice(device);
        interior_spread = 0.0f;
        if (output_device) {
            if (InteriorSet* set = output_device->getCurrentInteriorSet()) {
                if (Interior* interior = set->getInterior(interior_num))
                    interior_spread = interior->getUnk24();
            }
        }
    }

    f32 nearest_distance = FLT_MAX;
    for (s32 i = 0; i < cSegmentNum; ++i) {
        SpeakerBalanceUnifierAreaSegment* segment = mSegments[i];
        if (!segment->mHasPosition)
            continue;
        f32 distance = Meter::toMeter(std::sqrt(segment->mNearestSquaredDistance));
        f32 horizontal_distance = std::sqrt(segment->mSquaredDistance);
        if (mAttenuator && (mAttenuator->isListenerDirectivityEnabled() || _214)) {
            const f32 rate = listener.getDirectivity().calcDistRateLocal(segment->mPosition);
            distance *= rate;
            horizontal_distance *= rate;
        }
        nearest_distance = sead::Mathf::min(nearest_distance, distance);

        f32 gain = 1.0f;
        f32 curve_spread = 0.0f;
        if (mAttenuator) {
            const f32 volume = volume_curve ? volume_curve->interpolate(distance) : 1.0f;
            AttenuationCulling* culling = mAttenuator->getAttenuationCulling();
            const f32 culling_gain = culling ? culling->calcCullingGain(distance, volume_curve) :
                volume_curve ? AttenuationCulling::calcCullingGainByCurve(distance, volume_curve) : 1.0f;
            gain = volume * culling_gain;
            if (spread_curve)
                curve_spread = spread_curve->interpolate(distance);
        }
        if (max_gain)
            *max_gain = gain > *max_gain ? gain : *max_gain;

        for (s32 j = 0; j < device_num; ++j) {
            const DeviceType device(j);
            if (!(mgr->getEnabledDeviceMask() & (1 << int(device))))
                continue;
            SpeakerChannelVolume volume{};
            const f32 interior_size = mgr->getInteriorSize(interior_num);
            if (interior_size == 0.0f) {
                volume.volume[0] = gain * 180.285f;
                volume.volume[1] = gain * 180.285f;
            } else {
                f32 spread = curve_spread + mSpread;
                f32 distance_spread = 0.0f;
                if (horizontal_distance < interior_size) {
                    f32 ratio = horizontal_distance / interior_size;
                    if (spread < 0.0f) {
                        ratio = spread + 1.0f > 0.0f ? ratio / (spread + 1.0f) : 1.0f;
                        spread = 0.0f;
                    }
                    distance_spread = 1.0f - ratio;
                }
                spread = distance_spread > spread ? distance_spread : spread;
                if (interior_spread > 0.0f)
                    spread = interior_spread + (1.0f - interior_spread) * spread;
                if (spread <= 0.0f)
                    table->getSpeakerBalanceU8Range(&volume, i, device, interior_num);
                else
                    table->getSpeakerBalanceU8RangeWithSpread(
                        &volume, i, device, interior_num, spread > 1.0f ? 1.0f : spread);
                for (s32 channel = 0; channel < 5; ++channel)
                    volume.volume[channel] = gain * volume.volume[channel];
            }
            for (s32 channel = 0; channel < 5; ++channel) {
                if ((*volumes)[j].volume[channel] < volume.volume[channel])
                    (*volumes)[j].volume[channel] = volume.volume[channel];
            }
        }
    }
    calcAttenuationExceptVolume_(parameter, filter, priority_factor, nearest_distance);
}

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
// 0x7100b93d0c
void SpeakerBalanceUnifierArea::calcAttenuationExceptVolume_(f32* parameter, f32* filter,
                                                            f32* priority_factor,
                                                            f32 distance) const {
    if (distance == FLT_MAX || !mAttenuator) {
        *parameter = 0.0f;
        *filter = 0.0f;
        *priority_factor = 0.0f;
        return;
    }

    f32 parameter_value = 0.0f;
    f32 filter_value = 0.0f;
    if (Curve* curve = mAttenuator->getCurve(DistanceParamTarget::Unk1))
        parameter_value = curve->interpolate(distance);
    *parameter = parameter_value;
    if (Curve* curve = mAttenuator->getCurve(DistanceParamTarget::Filter))
        filter_value = curve->interpolate(distance);
    *filter = filter_value;
    Curve* priority_curve = mAttenuator->getCurve(DistanceParamTarget::PriorityFactor);
    *priority_factor = priority_curve ? priority_curve->interpolate(distance) : 1.0f;
    AttenuationCulling* culling = mAttenuator->getAttenuationCulling();
    if (culling && culling->isPriorityDownEnabled()) {
        const f32 gain = culling->calcCullingGain(distance, mAttenuator->getCurve(DistanceParamTarget::Volume));
        *priority_factor = gain * *priority_factor;
    }
}

}  // namespace aal
