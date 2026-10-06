#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include "aal/aalCone.h"

namespace aal {

/// How much a sound is heard depending on where it is relative to the listener: the rate is a mix of the
/// distance to the listener and the angle to the listener's cone (the cone axis is the listener direction).
/// The rate is `mMinRate` outside, `mMaxRate` inside and linear in between.
class ListenerDirectivity {
public:
    struct Settings {
        /// Cone angles in degrees.
        f32 cone_start_angle;
        f32 cone_end_angle;
        /// Distances in meters.
        f32 start_distance;
        f32 end_distance;
        f32 min_rate;
        f32 max_rate;
    };

    ListenerDirectivity();
    virtual ~ListenerDirectivity();

    void setParams(const Settings& settings);
    /// `position` is in world space; the cone position is subtracted.
    f32 calcDistRate(const sead::Vector3f& position) const;
    /// `local` is relative to the cone position.
    f32 calcDistRateLocal(const sead::Vector3f& local) const;

private:
    bool mEnabled;
    Cone mCone;
    f32 mStartDistance;
    f32 mEndDistance;
    f32 mDistanceRange;
    f32 mMinRate;
    f32 mMaxRate;
    f32 mRateRange;
    bool _78;
};
static_assert(sizeof(ListenerDirectivity) == 0x80, "aal::ListenerDirectivity size mismatch");

}  // namespace aal
