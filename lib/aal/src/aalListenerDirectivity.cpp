#include "aal/aalListenerDirectivity.h"
#include <math/seadMathCalcCommon.h>
#include "aal/aalMeter.h"

namespace aal {

// NON_MATCHING: the original does not merge the constant stores of the rate/distance fields
// 0x7100b84a24
ListenerDirectivity::ListenerDirectivity() {
    mEnabled = false;
    _78 = true;
    mStartDistance = 1.0f;
    mEndDistance = 5.0f;
    mDistanceRange = 4.0f;
    mMinRate = 0.5f;
    mMaxRate = 1.0f;
    mRateRange = 0.5f;
    mCone.setAngle(sead::Mathf::pi() / 8, sead::Mathf::pi() / 4);
}

// NON_MATCHING: same stores, different order / reloads of the rate fields
// 0x7100b84aa0
void ListenerDirectivity::setParams(const Settings& settings) {
    const f32 cDegToRad = sead::Mathf::pi() / 180;
    mCone.setAngle(settings.cone_start_angle * cDegToRad, settings.cone_end_angle * cDegToRad);
    mStartDistance = Meter::toLength(settings.start_distance);
    mEndDistance = Meter::toLength(settings.end_distance);
    mDistanceRange = mEndDistance - mStartDistance;
    mMinRate = settings.min_rate;
    mMaxRate = settings.max_rate;
    mEnabled = true;
    mRateRange = settings.max_rate - settings.min_rate;
}

// NON_MATCHING: calcDistRateLocal is inlined; the block layout of the early returns differs
// 0x7100b84b24
f32 ListenerDirectivity::calcDistRate(const sead::Vector3f& position) const {
    if (!mEnabled)
        return 1.0f;
    sead::Vector3f cone_position;
    mCone.getPosition(&cone_position);
    return calcDistRateLocal(position - cone_position);
}

// NON_MATCHING: block layout of the early `return mMinRate` paths differs
// 0x7100b84c74
f32 ListenerDirectivity::calcDistRateLocal(const sead::Vector3f& local) const {
    if (!mEnabled)
        return 1.0f;
    if (local.x == 0.0f && local.y == 0.0f && local.z == 0.0f)
        return mMinRate;

    f32 distance = local.length();
    if (mStartDistance >= distance)
        return mMinRate;
    f32 distance_rate;
    if (mEndDistance < distance) {
        distance_rate = 1.0f;
    } else {
        distance_rate = (distance - mStartDistance) / mDistanceRange;
        if (distance_rate == 0.0f)
            return mMinRate;
    }

    f32 cone_rate = mCone.calcRateOriginShiftPos(local);
    if (cone_rate == 0.0f)
        return mMinRate;

    f32 rate = distance_rate < cone_rate ? distance_rate : cone_rate;
    if (rate == 1.0f)
        return mMaxRate;
    return mMinRate + rate * mRateRange;
}

}  // namespace aal
