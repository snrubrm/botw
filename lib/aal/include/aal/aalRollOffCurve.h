#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// A roll off model (distance attenuation) as in OpenAL: gain 1 up to the reference distance, then falling to the
/// maximum distance. All functions of the models are const.
/// The names of the parameters follow the formulas of the models (verified against the two implementations).
class IRollOffCurveStrategy {
public:
    virtual ~IRollOffCurveStrategy() = default;

    /// The gain at `distance`. `pre_calc_factor` is the result of calcPreCalcFactor.
    virtual f32 calc(f32 distance, f32 ref_distance, f32 max_distance, f32 roll_off_factor,
                     f32 pre_calc_factor) const = 0;
    /// A factor of the formula that only depends on the parameters of the curve (cached by RollOffCurve).
    virtual f32 calcPreCalcFactor(f32 ref_distance, f32 max_distance, f32 roll_off_factor) const = 0;
    /// The inverse of calc: the parameter that gives `gain` at the other parameters. -1 if there is none.
    virtual f32 calcRolloff(f32 distance, f32 gain, f32 ref_distance, f32 max_distance) const = 0;
    virtual f32 calcRefDistance(f32 distance, f32 gain, f32 roll_off_factor, f32 max_distance) const = 0;
    virtual f32 calcDistance(f32 gain, f32 ref_distance, f32 roll_off_factor, f32 max_distance) const = 0;
};

/// gain = ref / (ref + roll_off * (distance - ref))
class RollOffCurveStrategyInv : public IRollOffCurveStrategy {
public:
    f32 calc(f32 distance, f32 ref_distance, f32 max_distance, f32 roll_off_factor,
             f32 pre_calc_factor) const override;
    f32 calcPreCalcFactor(f32 ref_distance, f32 max_distance, f32 roll_off_factor) const override;
    f32 calcRolloff(f32 distance, f32 gain, f32 ref_distance, f32 max_distance) const override;
    f32 calcRefDistance(f32 distance, f32 gain, f32 roll_off_factor, f32 max_distance) const override;
    f32 calcDistance(f32 gain, f32 ref_distance, f32 roll_off_factor, f32 max_distance) const override;
};

/// gain = 1 - roll_off * (distance - ref) / (max - ref)
class RollOffCurveStrategyLinear : public IRollOffCurveStrategy {
public:
    f32 calc(f32 distance, f32 ref_distance, f32 max_distance, f32 roll_off_factor,
             f32 pre_calc_factor) const override;
    f32 calcPreCalcFactor(f32 ref_distance, f32 max_distance, f32 roll_off_factor) const override;
    f32 calcRolloff(f32 distance, f32 gain, f32 ref_distance, f32 max_distance) const override;
    f32 calcRefDistance(f32 distance, f32 gain, f32 roll_off_factor, f32 max_distance) const override;
    f32 calcDistance(f32 gain, f32 ref_distance, f32 roll_off_factor, f32 max_distance) const override;
};

/// A curve that attenuates the volume with the distance. TODO: incomplete (the Curve base and most members are
/// not modeled).
class RollOffCurve {
public:
    /// The attenuation (0 - 1) at the given distance.
    f32 interpolate(f32 distance) const;
    void setRefDistance(f32 distance);
    void setMaxDistance(f32 distance);
    void setRollOffFactor(f32 factor);
    f32 getCullingStartDistance() const;

private:
    u8 _0[0x68];
    IRollOffCurveStrategy* mStrategy;
    f32 mRefDistance;
    f32 mMaxDistance;
    f32 mRollOffFactor;
    f32 mVolumeScale;
    bool mFlipped;
    u8 _81[0x84 - 0x81];
    f32 mCullingStartDistance;
    /// The result of IRollOffCurveStrategy::calcPreCalcFactor for the current parameters.
    f32 mCache;
};

}  // namespace aal
