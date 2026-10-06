#include <cmath>

#include "aal/aalSettings.h"
#include "aal/aalSystemAccessor.h"
#include "aal/aalTimedFader.h"

namespace aal {

// 0x7100b7c910
SimpleTimedFader::SimpleTimedFader(f32 value) {
    setValueImmediate(value);
}

// 0x7100b7c934
void SimpleTimedFader::setValueImmediate(f32 value) {
    mTarget = value;
    mValue = value;
    mNextValue = value;
    mStep = 0.0f;
}

inline void SimpleTimedFader::calcNextValue_() {
    const f32 time_step = SystemAccessor::getSettings()->mCalcTimeStep;
    f32 next = mValue + mStep * time_step;
    if (mStep >= 0.0f) {
        if (next > mTarget)
            next = mTarget;
    } else {
        if (next < mTarget)
            next = mTarget;
    }
    mNextValue = next;
}

// 0x7100b7c948
void SimpleTimedFader::calc() {
    if (mValue != mTarget) {
        mValue = mNextValue;
        calcNextValue_();
    }
}

// 0x7100b7c9b8
void SimpleTimedFader::moveTo(f32 target, f32 time) {
    if (time >= 0.0f) {
        mTarget = target;
        if (time != 0.0f && mValue != target) {
            mStep = (target - mValue) / time;
            calcNextValue_();
        } else {
            setValueImmediate(target);
        }
    }
}

// 0x7100b7ca4c
void SimpleTimedFader::moveToTargetByStep(f32 target, f32 step) {
    if (step >= 0.0f) {
        mTarget = target;
        if (step != 0.0f && mValue != target) {
            mStep = target - mValue > 0.0f ? step : -step;
            calcNextValue_();
        } else {
            setValueImmediate(target);
        }
    }
}

// 0x7100b7cae8
f32 SimpleTimedFader::toCurvedValue(FadeCurveType type, f32 value) {
    switch (type) {
    case FadeCurveType::Square:
        return value * value;
    case FadeCurveType::Sqrt:
        return std::sqrt(value);
    case FadeCurveType::Sin:
        return std::sin(value * 1.5707964f);
    default:
        return value;
    }
}

}  // namespace aal
