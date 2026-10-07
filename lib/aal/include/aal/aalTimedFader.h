#pragma once

#include <basis/seadTypes.h>

#include "aal/aalFadeCurveType.h"

namespace aal {

/// Moves a value towards a target in a given amount of time. The value is interpolated in the
/// curved domain selected by the fade curve type (the curved value is kept in sync with the target).
class TimedFader {
public:
    TimedFader(f32 value, FadeCurveType curve_type, f32 max_value);
    virtual ~TimedFader() = default;

    void setValueImmediate(f32 value);
    void calc();
    void moveTo(f32 target, f32 time);

    f32 getValue() const { return mValue; }
    f32 getNextValue() const { return mNextValue; }
    void setCurveType(FadeCurveType curve_type) { mCurveType = curve_type; }

private:
    /// Inline-only helper: converts a value to the curved domain (the inverse of the curve function).
    f32 toCurvedDomain_(f32 value) const;
    /// Inline-only helper: the inverse of toCurvedDomain_.
    f32 fromCurvedDomain_(f32 curved_value) const;

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

/// A fader that moves a value to a target in a given time (or by a given step per calculation). The value
/// advances one calculation step ahead: mValue is the current value and mNextValue the one of the next step.
class SimpleTimedFader {
public:
    explicit SimpleTimedFader(f32 value);
    virtual ~SimpleTimedFader() = default;

    void setValueImmediate(f32 value);
    void calc();
    /// Moves to the target in `time` seconds; a negative time is ignored and zero jumps to the target.
    void moveTo(f32 target, f32 time);
    /// Moves to the target by `step` per second (the sign is chosen towards the target).
    void moveToTargetByStep(f32 target, f32 step);
    /// 0x7100b7cae8: converts a linear value to the curved domain of the fade curve type.
    static f32 toCurvedValue(FadeCurveType type, f32 value);
    f32 getValue() const { return mValue; }
    f32 getTarget() const { return mTarget; }

private:
    /// Inline-only helper: mNextValue = mValue + step * time step, not passing the target.
    void calcNextValue_();

    f32 mValue;
    f32 mNextValue;
    f32 mTarget;
    f32 mStep;
};
static_assert(sizeof(SimpleTimedFader) == 0x18, "aal::SimpleTimedFader size mismatch");

}  // namespace aal
