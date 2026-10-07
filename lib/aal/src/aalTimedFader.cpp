#include <algorithm>
#include <cmath>

#include "aal/aalSettings.h"
#include "aal/aalSystem.h"
#include "aal/aalSystemAccessor.h"
#include "aal/aalTimedFader.h"

namespace aal {

namespace {
constexpr f32 cHalfPi = 1.5707964f;
}  // namespace

inline f32 TimedFader::toCurvedDomain_(f32 value) const {
    if (mCurveType == FadeCurveType::Linear || mMaxValue == 0.0f)
        return value;

    const f32 sign = value >= 0.0f ? 1.0f : -1.0f;
    const f32 ratio = std::min((value > 0.0f ? value : -value) / mMaxValue, 1.0f);
    switch (mCurveType) {
    case FadeCurveType::Square:
        return sign * std::sqrt(ratio) * mMaxValue;
    case FadeCurveType::Sqrt:
        return mMaxValue * (ratio * (sign * ratio));
    case FadeCurveType::Sin:
        return mMaxValue * (sign * std::asin(ratio) / cHalfPi);
    default:
        return value;
    }
}

/// Inline-only helper: converts a value of the curved domain back to a value.
inline f32 TimedFader::fromCurvedDomain_(f32 curved_value) const {
    if (mCurveType == FadeCurveType::Linear || mMaxValue == 0.0f)
        return curved_value;

    const f32 sign = curved_value >= 0.0f ? 1.0f : -1.0f;
    const f32 ratio = std::min((curved_value > 0.0f ? curved_value : -curved_value) / mMaxValue, 1.0f);
    switch (mCurveType) {
    case FadeCurveType::Square:
        return mMaxValue * (ratio * (sign * ratio));
    case FadeCurveType::Sqrt:
        return sign * std::sqrt(ratio) * mMaxValue;
    case FadeCurveType::Sin:
        return sign * std::sin(ratio * cHalfPi) * mMaxValue;
    default:
        return curved_value;
    }
}

// 0x7100b7cb54
TimedFader::TimedFader(f32 value, FadeCurveType curve_type, f32 max_value)
    : mCurveType(curve_type), mMaxValue(max_value) {
    const f32 curved = toCurvedDomain_(value);
    mNextValue = value;
    mValue = value;
    mCurvedValue = curved;
    mCurvedNextValue = curved;
    mCurvedTargetValue = curved;
    mCurvedStep = 0.0f;
}

// 0x7100b7cc50
void TimedFader::setValueImmediate(f32 value) {
    const f32 curved = toCurvedDomain_(value);
    mNextValue = value;
    mValue = value;
    mCurvedValue = curved;
    mCurvedNextValue = curved;
    mCurvedTargetValue = curved;
    mCurvedStep = 0.0f;
}

// NON_MATCHING: same instructions; different registers for the step of the next value.
// 0x7100b7cd38
void TimedFader::calc() {
    if (mCurvedValue == mCurvedTargetValue)
        return;

    mCurvedValue = mCurvedNextValue;
    if (mCurvedValue == mCurvedTargetValue) {
        mValue = mNextValue;
        return;
    }

    mValue = fromCurvedDomain_(mCurvedValue);

    const f32 current = mCurvedValue;
    f32 next = current + System::sInstance->mSettings->mCalcTimeStep * mCurvedStep;
    if (mCurvedStep >= 0.0f) {
        if (next > mCurvedTargetValue)
            next = mCurvedTargetValue;
    } else {
        if (next < mCurvedTargetValue)
            next = mCurvedTargetValue;
    }
    mCurvedNextValue = next;
}

}  // namespace aal
