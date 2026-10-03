#pragma once

#include <basis/seadTypes.h>

#include "aal/aalFadeCurveType.h"

namespace aal {

/// Moves a value towards a target in a given amount of time. The value is interpolated in the
/// curved domain selected by the fade curve type (the curved value is kept in sync with the target).
class TimedFader {
public:
    TimedFader(f32 value, FadeCurveType curve_type, f32 max_value);
    virtual ~TimedFader();

    void setValueImmediate(f32 value);
    void calc();
    void moveTo(f32 target, f32 time);

    f32 getValue() const { return mValue; }
    void setCurveType(FadeCurveType curve_type) { mCurveType = curve_type; }

private:
    f32 mValue;
    f32 mNextValue;
    f32 mCurvedValue;
    f32 mCurvedNextValue;
    f32 mCurvedTargetValue;
    f32 mCurvedStep = 0.0f;
    FadeCurveType mCurveType;
    f32 mMaxValue;
};
static_assert(sizeof(TimedFader) == 0x28, "aal::TimedFader size mismatch");

}  // namespace aal
