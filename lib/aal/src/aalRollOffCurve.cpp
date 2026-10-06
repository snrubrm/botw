#include "aal/aalRollOffCurve.h"
#include <cfloat>
#include <math/seadMathCalcCommon.h>

namespace aal {

// 0x7100ba436c
f32 RollOffCurve::interpolate(f32 distance) const {
    if (!mStrategy)
        return mVolumeScale;
    const f32 max_distance = mMaxDistance == 0.0f ? FLT_MAX : mMaxDistance;
    const f32 volume =
        mStrategy->interpolate_(distance, mRefDistance, max_distance, mRollOffFactor, mCache);
    const f32 result = mFlipped ? 1.0f - volume * (1.0f - mVolumeScale) : volume * mVolumeScale;
    return sead::Mathf::clamp(result, 0.0f, 1.0f);
}

// 0x7100ba44ac
void RollOffCurve::setRefDistance(f32 distance) {
    if (distance > 0.0f) {
        mRefDistance = distance;
        if (mStrategy)
            mCache = mStrategy->calcCache_(mRefDistance, mMaxDistance, mRollOffFactor);
    }
}

// 0x7100ba44f0
void RollOffCurve::setMaxDistance(f32 distance) {
    if (distance >= 0.0f) {
        mMaxDistance = distance;
        if (mStrategy)
            mCache = mStrategy->calcCache_(mRefDistance, mMaxDistance, mRollOffFactor);
    }
}

// 0x7100ba453c
void RollOffCurve::setRollOffFactor(f32 factor) {
    if (factor >= 0.0f) {
        mRollOffFactor = factor;
        if (mStrategy)
            mCache = mStrategy->calcCache_(mRefDistance, mMaxDistance, mRollOffFactor);
    }
}

// 0x7100ba562c
f32 RollOffCurve::getCullingStartDistance() const {
    return mCullingStartDistance;
}

}  // namespace aal
