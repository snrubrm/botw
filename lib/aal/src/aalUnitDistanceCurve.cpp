#include "aal/aalUnitDistanceCurve.h"
#include <math/seadMathCalcCommon.h>

namespace aal {

// NON_MATCHING: same code; different order of the initial stores and of the operands of the final addition.
// 0x7100ba5bac
UnitDistanceCurve::UnitDistanceCurve(const sead::SafeString& name) : Curve(name) {
    calcCullingStartDistance_();
}

void UnitDistanceCurve::calcCullingStartDistance_() {
    f32 value = 0.0f;
    f32 offset = 0.0f;
    f32 scale = 1.0f;
    switch (mCurveType) {
    case CurveType::Log:
        value = sead::Mathf::logTable(3.0517578e-05f) / sead::Mathf::logTable(mDecayRatio);
        offset = mHoldDistance;
        scale = mUnitDistance;
        break;
    case CurveType::Linear:
        value = 1.99993896f;
        break;
    default:
        break;
    }
    mCullingStartDistance = offset + value * scale;
}

}  // namespace aal
