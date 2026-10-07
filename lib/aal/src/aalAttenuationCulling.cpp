#include "aal/aalAttenuationCulling.h"
#include "aal/aalAttenuationReader.h"
#include "aal/aalCurve.h"

namespace aal {

// 0x7100bb7c00
AttenuationCulling::AttenuationCulling(const sead::SafeString& name)  {
    setObjName(name);
}

// 0x7100bb7d8c
f32 AttenuationCulling::calcCullingGain(f32 distance, f32 culling_distance, f32 culling_mergin) {
    if (culling_distance <= 0.0f)
        return 1.0f;
    if (distance >= culling_distance)
        return 0.0f;
    if (culling_mergin <= 0.0f)
        return 1.0f;
    const f32 fade_start = culling_distance - culling_mergin;
    if (fade_start >= distance)
        return 1.0f;
    const f32 gain = 1.0f - (distance - fade_start) / culling_mergin;
    return gain * gain;
}

// 0x7100bb7dd8
f32 AttenuationCulling::calcCullingGain(f32 distance, Curve* curve) const {
    if (curve) {
        const f32 start = curve->getCullingStartDistance();
        if (start == 0.0f)
            return calcCullingGain(distance, mCullingDistance, mCullingMergin);
        return calcCullingGain(distance, start + mCullingMergin, mCullingMergin);
    }
    return calcCullingGain(distance, mCullingDistance, mCullingMergin);
}

// NON_MATCHING: the original keeps the two comparisons as branches (a select is built here).
// 0x7100bb7ec0
f32 AttenuationCulling::calcCullingGainByCurve(f32 distance, Curve* curve) {
    const f32 start = curve->getCullingStartDistance();
    if (start <= 0.0f)
        return 1.0f;
    if (start > distance)
        return 1.0f;
    return 0.0f;
}

// 0x7100bb7f04
void AttenuationCulling::setupFromResourceReader(const AttenuationCullingReader& reader) {
    if (!reader.isValid())
        return;

    const f32 culling_distance = reader.getCullingDistance();
    if (culling_distance >= 0.0f) {
        mCullingDistance = culling_distance;
        if (mCullingMergin > mCullingDistance)
            mCullingDistance = mCullingMergin;
        mCullingStartDistance = mCullingDistance - mCullingMergin;
    }

    const f32 culling_mergin = reader.getCullingMergin();
    if (culling_mergin >= 0.0f) {
        mCullingMergin = culling_mergin;
        if (mCullingDistance < mCullingMergin)
            mCullingDistance = mCullingMergin;
        mCullingStartDistance = mCullingDistance - mCullingMergin;
    }

    mPriorityDown = reader.isPriorityDownEnabled();
}

}  // namespace aal
