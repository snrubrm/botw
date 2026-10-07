#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "aal/aalCurve.h"

namespace sead {
class Heap;
}

namespace aal {

class CustomCurveReader;
class CustomCurveSegment;

/// A curve that is made of segments (a list of positions, values and shapes). TODO: only the construction is
/// implemented.
class CustomCurve : public Curve {
    SEAD_RTTI_OVERRIDE(CustomCurve, Curve)
public:
    explicit CustomCurve(const sead::SafeString& name);
    ~CustomCurve() override;

    f32 interpolate(f32 x) const override;
    void drawGraph(sead::DrawContext* context, sead::TextWriter* writer, const DrawGraphArg* arg) const override;
    void draw3DGraph(sead::DrawContext* context, const sead::Camera& camera, const sead::Projection& projection,
                     const sead::Viewport& viewport, const Curve3DDrawArg* arg) const override;
    void saveToXmlDocument(bool save_as_host_file) override;
    void loadFromXmlDocument(const sead::SafeString& path) override;

    void setupFromResourceReader(const CustomCurveReader& reader, sead::Heap* heap);
    void addSegment(CustomCurveSegment* segment);

private:
    sead::OffsetList<CustomCurveSegment> mSegments;
    void* _80 = nullptr;
    f32 _88 = 1.0f;
    f32 _8c = 0.0f;
    f32 _90 = 1.0f;
    f32 _94 = 1.0f;
    bool _98 = false;
    bool _99 = false;
    DrawGraphArg mDrawGraphArg;
    s32 _f0 = 0;
    bool _f4 = false;
};
static_assert(sizeof(CustomCurve) == 0xf8, "aal::CustomCurve size mismatch");

}  // namespace aal
