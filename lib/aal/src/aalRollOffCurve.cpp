#include "aal/aalRollOffCurve.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <limits>
#include <basis/seadNew.h>
#include <math/seadMathCalcCommon.h>
#include "aal/aalCurveReader.h"

namespace aal {

RollOffCurve::~RollOffCurve() = default;

// 0x7100ba4130
RollOffCurve::RollOffCurve(const sead::SafeString& name) : Curve(name) {}

// 0x7100ba4400
void RollOffCurve::createAndSetStrategy(RollOffModel model, sead::Heap* heap) {
    mModel = model;
    switch (model) {
    case RollOffModel::Exp:
        mStrategy = new (heap) RollOffCurveStrategyExp;
        break;
    case RollOffModel::Linear:
        mStrategy = new (heap) RollOffCurveStrategyLinear;
        break;
    case RollOffModel::Inverse:
        mStrategy = new (heap) RollOffCurveStrategyInv;
        break;
    default:
        mStrategy = nullptr;
        return;
    }
    if (mStrategy)
        mCache = mStrategy->calcPreCalcFactor(mRefDistance, mMaxDistance, mRollOffFactor);
}

// 0x7100ba4584
void RollOffCurve::setupFromResourceReader(const RollOffCurveReader& reader, sead::Heap* heap) {
    if (!reader.isValid())
        return;
    createAndSetStrategy(reader.getRollOffModel(), heap);
    setRefDistance(reader.getRefDistance());
    setMaxDistance(reader.getMaxDistance());
    setRollOffFactor(reader.getRollOffFactor());
    const f32 start_value = reader.getStartValue();
    if (start_value >= 0.0f && start_value <= 1.0f)
        mVolumeScale = start_value;
    mFlipped = reader.isIncreaseMode();
    const f32 culling_start_distance = reader.getCullingStartDistance();
    if (culling_start_distance >= 0.0f)
        mCullingStartDistance = culling_start_distance;
}

// 0x7100ba436c
f32 RollOffCurve::interpolate(f32 distance) const {
    if (!mStrategy)
        return mVolumeScale;
    const f32 max_distance = mMaxDistance == 0.0f ? FLT_MAX : mMaxDistance;
    const f32 volume =
        mStrategy->calc(distance, mRefDistance, max_distance, mRollOffFactor, mCache);
    const f32 result = mFlipped ? 1.0f - volume * (1.0f - mVolumeScale) : volume * mVolumeScale;
    return sead::Mathf::clamp(result, 0.0f, 1.0f);
}

// 0x7100ba44ac
void RollOffCurve::setRefDistance(f32 distance) {
    if (distance > 0.0f) {
        mRefDistance = distance;
        if (mStrategy)
            mCache = mStrategy->calcPreCalcFactor(mRefDistance, mMaxDistance, mRollOffFactor);
    }
}

// 0x7100ba44f0
void RollOffCurve::setMaxDistance(f32 distance) {
    if (distance >= 0.0f) {
        mMaxDistance = distance;
        if (mStrategy)
            mCache = mStrategy->calcPreCalcFactor(mRefDistance, mMaxDistance, mRollOffFactor);
    }
}

// 0x7100ba453c
void RollOffCurve::setRollOffFactor(f32 factor) {
    if (factor >= 0.0f) {
        mRollOffFactor = factor;
        if (mStrategy)
            mCache = mStrategy->calcPreCalcFactor(mRefDistance, mMaxDistance, mRollOffFactor);
    }
}

// 0x7100ba562c
f32 RollOffCurve::getCullingStartDistance() const {
    return mCullingStartDistance;
}


namespace {
// sead::Mathf::powTable is declared by sead but not defined; this is its (inline) definition: pow with the exp / log
// tables. x == 0 is handled separately (the log of zero is undefined).
f32 powTable(f32 x, f32 y) {
    if (x == 0.0f) {
        if (y > 0.0f)
            return 0.0f;
        if (y < 0.0f)
            return std::numeric_limits<f32>::infinity();
        return 1.0f;
    }
    return sead::Mathf::expTable(sead::Mathf::logTable(x) * y);
}

// Gains this close to zero are rounded to zero (the two limits are not symmetric).
constexpr f32 cGainEpsilonPositive = 3.0518509e-05f;
constexpr f32 cGainEpsilonNegative = -3.0517578e-05f;
constexpr f32 cMinGain = 3.0518509e-05f;

inline f32 roundSmallGain(f32 gain) {
    return gain > cGainEpsilonNegative && gain < cGainEpsilonPositive ? 0.0f : gain;
}
}  // namespace

// 0x7100ba5634
f32 RollOffCurveStrategyInv::calc(f32 distance, f32 ref_distance, f32 max_distance,
                                  f32 roll_off_factor, f32 pre_calc_factor) const {
    if (distance <= ref_distance)
        return 1.0f;
    if (distance >= max_distance)
        distance = max_distance;
    return roundSmallGain(ref_distance / (distance * roll_off_factor + pre_calc_factor));
}

// 0x7100ba567c
f32 RollOffCurveStrategyInv::calcPreCalcFactor(f32 ref_distance, f32, f32 roll_off_factor) const {
    return (1.0f - roll_off_factor) * ref_distance;
}

// 0x7100ba568c
f32 RollOffCurveStrategyInv::calcRolloff(f32 distance, f32 gain, f32 ref_distance, f32) const {
    if (ref_distance <= 0.0f || distance <= ref_distance)
        return -1.0f;
    gain = std::max(gain, cMinGain);
    return (1.0f - gain) * ref_distance / (gain * (distance - ref_distance));
}

// 0x7100ba56cc
f32 RollOffCurveStrategyInv::calcRefDistance(f32 distance, f32 gain, f32 roll_off_factor,
                                             f32) const {
    if (distance <= 0.0f || roll_off_factor <= 0.0f)
        return -1.0f;
    gain = std::max(gain, cMinGain);
    const f32 denominator = 1.0f - gain * (1.0f - roll_off_factor);
    if (denominator <= 0.0f)
        return -1.0f;
    const f32 ref_distance = gain * roll_off_factor * distance / denominator;
    return !(ref_distance <= 0.0f) ? ref_distance : -1.0f;
}

// 0x7100ba5724
f32 RollOffCurveStrategyInv::calcDistance(f32 gain, f32 ref_distance, f32 roll_off_factor,
                                          f32) const {
    if (ref_distance <= 0.0f || roll_off_factor <= 0.0f)
        return -1.0f;
    const f32 denominator = gain * roll_off_factor;
    if (denominator <= 0.0f)
        return -1.0f;
    return (1.0f - std::max(gain, cMinGain)) * ref_distance / denominator + ref_distance;
}

// 0x7100ba576c
f32 RollOffCurveStrategyLinear::calc(f32 distance, f32 ref_distance, f32 max_distance,
                                     f32 roll_off_factor, f32 pre_calc_factor) const {
    if (distance <= ref_distance)
        return 1.0f;
    if (distance >= max_distance)
        distance = max_distance;
    return roundSmallGain(1.0f - (distance - ref_distance) * pre_calc_factor);
}

// 0x7100ba57b8
f32 RollOffCurveStrategyLinear::calcPreCalcFactor(f32 ref_distance, f32 max_distance,
                                                  f32 roll_off_factor) const {
    return roll_off_factor / (max_distance - ref_distance);
}

// 0x7100ba57c4
f32 RollOffCurveStrategyLinear::calcRolloff(f32 distance, f32 gain, f32 ref_distance,
                                            f32 max_distance) const {
    if (distance <= ref_distance || ref_distance >= max_distance)
        return -1.0f;
    return (1.0f - gain) * (max_distance - ref_distance) / (distance - ref_distance);
}

// 0x7100ba57f8
f32 RollOffCurveStrategyLinear::calcRefDistance(f32 distance, f32 gain, f32 roll_off_factor,
                                                f32 max_distance) const {
    if (distance <= 0.0f || roll_off_factor <= 0.0f || max_distance <= 0.0f)
        return -1.0f;
    gain = std::max(gain, cMinGain);
    const f32 denominator = gain + roll_off_factor + -1.0f;
    if (denominator == 0.0f)
        return -1.0f;
    return (distance * roll_off_factor - (1.0f - gain) * max_distance) / denominator;
}

// 0x7100ba5854
f32 RollOffCurveStrategyLinear::calcDistance(f32 gain, f32 ref_distance, f32 roll_off_factor,
                                             f32 max_distance) const {
    if (ref_distance <= 0.0f || roll_off_factor <= 0.0f || max_distance <= 0.0f)
        return -1.0f;
    return (1.0f - std::max(gain, cMinGain)) * (max_distance - ref_distance) / roll_off_factor +
           ref_distance;
}

// 0x7100ba589c
f32 RollOffCurveStrategyExp::calc(f32 distance, f32 ref_distance, f32 max_distance, f32 roll_off_factor,
                                  f32 pre_calc_factor) const {
    if (distance <= ref_distance)
        return 1.0f;
    if (distance >= max_distance)
        distance = max_distance;
    return roundSmallGain(powTable(distance, -roll_off_factor) * pre_calc_factor);
}

// 0x7100ba593c
f32 RollOffCurveStrategyExp::calcPreCalcFactor(f32 ref_distance, f32, f32 roll_off_factor) const {
    return powTable(1.0f / ref_distance, -roll_off_factor);
}

// 0x7100ba59a8
f32 RollOffCurveStrategyExp::calcRolloff(f32 distance, f32 gain, f32 ref_distance, f32) const {
    if (ref_distance <= 0.0f || distance <= ref_distance)
        return -1.0f;
    gain = std::max(gain, cMinGain);
    return sead::Mathf::logTable(1.0f / gain) / sead::Mathf::logTable(distance / ref_distance);
}

// 0x7100ba5a0c
f32 RollOffCurveStrategyExp::calcRefDistance(f32 distance, f32 gain, f32 roll_off_factor, f32) const {
    if (distance <= 0.0f || roll_off_factor <= 0.0f)
        return -1.0f;
    gain = std::max(gain, cMinGain);
    const f32 ref_distance =
        distance / powTable(1.0f / gain, 1.0f / roll_off_factor);
    return !(ref_distance <= 0.0f) ? ref_distance : -1.0f;
}

// 0x7100ba5a9c
f32 RollOffCurveStrategyExp::calcDistance(f32 gain, f32 ref_distance, f32 roll_off_factor, f32) const {
    if (ref_distance <= 0.0f || roll_off_factor <= 0.0f)
        return -1.0f;
    gain = std::max(gain, cMinGain);
    return powTable(1.0f / gain, 1.0f / roll_off_factor) * ref_distance;
}

}  // namespace aal
