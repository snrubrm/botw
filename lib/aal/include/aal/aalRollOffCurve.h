#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The calculation of a roll off model (inverse distance, linear...) used by RollOffCurve.
/// TODO: the semantic of both virtuals is a guess from the callers; names are placeholders.
class RollOffStrategy {
public:
    virtual ~RollOffStrategy() = default;

    /// Called by RollOffCurve::interpolate with the curve parameters, the factor and the cached value.
    virtual f32 interpolate_(f32 a, f32 ref_distance, f32 max_distance, f32 roll_off_factor, f32 cache) const = 0;
    /// Recalculates the cached value of the curve after a parameter changed.
    virtual f32 calcCache_(f32 ref_distance, f32 max_distance, f32 roll_off_factor) const = 0;
};

/// A curve that attenuates the volume with the distance. TODO: incomplete (the Curve base and most members are
/// not modeled).
class RollOffCurve {
public:
    void setRefDistance(f32 distance);
    void setMaxDistance(f32 distance);
    void setRollOffFactor(f32 factor);
    f32 getCullingStartDistance() const;

private:
    u8 _0[0x68];
    RollOffStrategy* mStrategy;
    f32 mRefDistance;
    f32 mMaxDistance;
    f32 mRollOffFactor;
    u8 _7c[0x84 - 0x7c];
    f32 mCullingStartDistance;
    /// The result of RollOffStrategy::calcCache_ for the current parameters.
    f32 mCache;
};

}  // namespace aal
