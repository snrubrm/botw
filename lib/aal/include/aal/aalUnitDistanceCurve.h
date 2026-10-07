#pragma once

#include <basis/seadTypes.h>
#include <prim/seadEnum.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "aal/aalCurve.h"

namespace sead {
class Heap;
}

namespace aal {

class UnitDistanceCurveReader;

/// A curve that decays by a ratio over every unit distance (after a hold distance). TODO: the setup from a resource,
/// the XML and the graph drawing are not implemented.
class UnitDistanceCurve : public Curve {
    SEAD_RTTI_OVERRIDE(UnitDistanceCurve, Curve)
public:
    SEAD_ENUM(CurveType, Log, Linear)

    explicit UnitDistanceCurve(const sead::SafeString& name);
    ~UnitDistanceCurve() override = default;

    f32 interpolate(f32 distance) const override;
    f32 getCullingStartDistance() const override { return mCullingStartDistance; }
    void drawGraph(sead::DrawContext* context, sead::TextWriter* writer, const DrawGraphArg* arg) const override;
    void draw3DGraph(sead::DrawContext* context, const sead::Camera& camera, const sead::Projection& projection,
                     const sead::Viewport& viewport, const Curve3DDrawArg* arg) const override;
    void saveToXmlDocument(bool save_as_host_file) override;
    void loadFromXmlDocument(const sead::SafeString& path) override;

    void setupFromResourceReader(const UnitDistanceCurveReader& reader, sead::Heap* heap);

private:
    /// The distance after which the curve is practically zero.
    void calcCullingStartDistance_();

    CurveType mCurveType = CurveType(0);
    f32 mStartValue = 1.0f;
    f32 mEndValue = 0.0f;
    f32 mHoldDistance = 0.0f;
    f32 mUnitDistance = 1.0f;
    f32 mDecayRatio = 0.5f;
    s32 _80 = 0;
    f32 mCullingStartDistance = 3.4028235e+38f;
    bool _88 = false;
    bool _89 = false;
    DrawGraphArg mDrawGraphArg;
    f32 _e0 = 0.1f;
    s32 _e4 = 0;
    bool _e8 = false;
};
static_assert(sizeof(UnitDistanceCurve) == 0xf0, "aal::UnitDistanceCurve size mismatch");

}  // namespace aal
