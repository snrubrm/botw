#include "aal/aalUnitDistanceCurve.h"
#include "aal/aalCurveReader.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <math/seadMathCalcCommon.h>

namespace aal {

// 0x7100ba5bac
UnitDistanceCurve::UnitDistanceCurve(const sead::SafeString& name) : Curve(name) {
    calcCullingDistance_();
}

// 0x7100ba5e48
f32 UnitDistanceCurve::interpolate(f32 distance) const {
    if (mHoldDistance >= distance)
        return mStartValue;
    if (mCullingDistance < distance)
        return 0.0f;
    if (mDecayRatio == 1.0f)
        return mStartValue;
    if (mDecayRatio == 0.0f)
        return mEndValue;

    const f32 elapsed = distance - mHoldDistance;
    f32 rate = 0.0f;
    switch (mCurveType) {
    case CurveType::Log:
        rate = std::pow(mDecayRatio, elapsed / mUnitDistance);
        break;
    case CurveType::Linear:
        rate = std::max(1.0f - elapsed / mUnitDistance * (1.0f - mDecayRatio), 0.0f);
        break;
    default:
        break;
    }

    const f32 value = mEndValue + (mStartValue - mEndValue) * rate;
    return value > -3.0517578e-05f && value < 3.0518509e-05f ? 0.0f : value;
}

void UnitDistanceCurve::calcCullingDistance_() {
    mCullingDistance = FLT_MAX;
    if (mStartValue < mEndValue)
        return;
    if (mStartValue <= 0.0f) {
        mCullingDistance = 0.0f;
        return;
    }
    if (mEndValue > 0.0f)
        return;
    if (mDecayRatio == 0.0f) {
        mCullingDistance = mHoldDistance;
        return;
    }

    const f32 limit = std::max((0.0f - mEndValue) / (mStartValue - mEndValue), 3.0517578e-05f);
    f32 distance = 0.0f;
    switch (mCurveType) {
    case CurveType::Log:
        distance = sead::Mathf::logTable(limit) / sead::Mathf::logTable(mDecayRatio) * mUnitDistance;
        break;
    case CurveType::Linear:
        distance = (1.0f - limit) / (1.0f - mDecayRatio) * mUnitDistance;
        break;
    default:
        break;
    }
    mCullingDistance = mHoldDistance + distance;
}

// NON_MATCHING: same code; the comparison of the start and the end value has its operands the other way round at the
// inlined copies of the culling distance calculation, and the operands of a multiplication and an addition are swapped.
// 0x7100ba5f38
void UnitDistanceCurve::setupFromResourceReader(const UnitDistanceCurveReader& reader, sead::Heap*) {
    if (!reader.isValid())
        return;

    mCurveType = reader.getCurveType();
    calcCullingDistance_();

    const f32 start_value = reader.getStartValue();
    if (start_value >= 0.0f && start_value <= 1.0f) {
        mStartValue = start_value;
        calcCullingDistance_();
    }

    const f32 end_value = reader.getEndValue();
    if (end_value >= 0.0f && end_value <= 1.0f) {
        mEndValue = end_value;
        calcCullingDistance_();
    }

    const f32 hold_distance = reader.getHoldDistance();
    if (hold_distance >= 0.0f) {
        mHoldDistance = hold_distance;
        calcCullingDistance_();
    }

    const f32 unit_distance = reader.getUnitDistance();
    if (unit_distance > 0.0f) {
        mUnitDistance = unit_distance;
        calcCullingDistance_();
    }

    const f32 decay_ratio = reader.getDecayRatio();
    if (decay_ratio >= 0.0f && decay_ratio <= 1.0f) {
        mDecayRatio = decay_ratio;
        calcCullingDistance_();
    }

    const f32 culling_start_distance = reader.getCullingStartDistance();
    if (culling_start_distance >= 0.0f)
        mCullingStartDistance = culling_start_distance;
}

}  // namespace aal
