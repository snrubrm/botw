#include <algorithm>
#include <cmath>

#include "aal/aalSettings.h"
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

}  // namespace aal
