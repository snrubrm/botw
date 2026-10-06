#include "aal/aalRollOffCurve.h"

namespace aal {

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
