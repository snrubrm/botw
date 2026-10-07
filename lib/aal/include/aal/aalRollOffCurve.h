#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "aal/aalCurve.h"

namespace aal {

/// The roll off model of a RollOffCurve (the strategy that is used).
SEAD_ENUM(RollOffModel, None, Inverse, Linear, Exp);

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

/// The exponential roll off model.
class RollOffCurveStrategyExp : public IRollOffCurveStrategy {
public:
    f32 calc(f32 distance, f32 ref_distance, f32 max_distance, f32 roll_off_factor,
             f32 pre_calc_factor) const override;
    f32 calcPreCalcFactor(f32 ref_distance, f32 max_distance, f32 roll_off_factor) const override;
    f32 calcRolloff(f32 distance, f32 gain, f32 ref_distance, f32 max_distance) const override;
    f32 calcRefDistance(f32 distance, f32 gain, f32 roll_off_factor, f32 max_distance) const override;
    f32 calcDistance(f32 gain, f32 ref_distance, f32 roll_off_factor, f32 max_distance) const override;
};

class RollOffCurveReader;

/// A curve that attenuates the volume with the distance. TODO: the XML and the graph drawing are not implemented.
class RollOffCurve : public Curve {
    SEAD_RTTI_OVERRIDE(RollOffCurve, Curve)
public:
    explicit RollOffCurve(const sead::SafeString& name);
    ~RollOffCurve() override = default;

    /// The attenuation (0 - 1) at the given distance.
    f32 interpolate(f32 distance) const override;
    f32 getCullingStartDistance() const override;
    void drawGraph(sead::DrawContext* context, sead::TextWriter* writer, const DrawGraphArg* arg) const override;
    void draw3DGraph(sead::DrawContext* context, const sead::Camera& camera, const sead::Projection& projection,
                     const sead::Viewport& viewport, const Curve3DDrawArg* arg) const override;
    void saveToXmlDocument(bool save_as_host_file) override;
    void loadFromXmlDocument(const sead::SafeString& path) override;

    /// Replaces the strategy (the formula) by a new one of the model.
    void createAndSetStrategy(RollOffModel model, sead::Heap* heap);
    void setupFromResourceReader(const RollOffCurveReader& reader, sead::Heap* heap);
    void setRefDistance(f32 distance);
    void setMaxDistance(f32 distance);
    void setRollOffFactor(f32 factor);

private:
    IRollOffCurveStrategy* mStrategy = nullptr;
    f32 mRefDistance = 1.0f;
    f32 mMaxDistance = 0.0f;
    f32 mRollOffFactor = 1.0f;
    f32 mVolumeScale = 1.0f;
    bool mFlipped = false;
    f32 mCullingStartDistance = 0.0f;
    /// The result of IRollOffCurveStrategy::calcPreCalcFactor for the current parameters.
    f32 mCache = 0.0f;
    RollOffModel mModel;
    bool _90 = false;
    bool _91 = false;
    DrawGraphArg mDrawGraphArg;
    f32 _e8 = 0.1f;
    s32 _ec = 0;
    bool _f0 = false;
};
static_assert(sizeof(RollOffCurve) == 0xf8, "aal::RollOffCurve size mismatch");

}  // namespace aal
