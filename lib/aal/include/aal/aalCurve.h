#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <container/seadListImpl.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "aal/aalNamedObj.h"

namespace sead {
class Camera;
class DrawContext;
class Projection;
class TextWriter;
class Viewport;
}  // namespace sead

namespace aal {

struct Curve3DDrawArg;

/// A curve that maps a value (a distance, usually) to a gain, edited and shown (graph drawing) in the debug tools.
/// The subclasses are the CustomCurve, the RollOffCurve and the UnitDistanceCurve.
class Curve : public FixedNamedObj<32>, public sead::hostio::Node {
    SEAD_RTTI_BASE(Curve)
public:
    /// How the graph of a curve is drawn. The arguments of the debug graph drawing, with the defaults of the original
    /// (the meanings of the fields are not known).
    struct DrawGraphArg {
        f32 _0 = 200.0f;
        f32 _4 = 300.0f;
        f32 _8 = 100.0f;
        f32 _c = 800.0f;
        f32 _10 = 400.0f;
        f32 _14 = 10.0f;
        f32 _18 = 0.1f;
        s32 _1c = 128;
        f32 _20 = 5.0f;
        sead::Color4f _24 = sead::Color4f::cWhite;
        f32 _34 = 0.1f;
        f32 _38 = 0.1f;
        f32 _3c = 0.1f;
        f32 _40 = 0.5f;
        s32 _44 = 0;
        s32 _48 = 0;
        s32 _4c = 0;
        bool _50 = true;
        bool _51 = true;
        bool _52 = true;
    };
    static_assert(sizeof(DrawGraphArg) == 0x54, "aal::Curve::DrawGraphArg size mismatch");

    explicit Curve(const sead::SafeString& name) { setObjName(name); }

    /// The value of the curve at `x`.
    virtual f32 interpolate(f32 x) const = 0;
    virtual f32 getCullingStartDistance() const { return 0.0f; }
    virtual void drawGraph(sead::DrawContext*, sead::TextWriter*, const DrawGraphArg*) const {}
    virtual void draw3DGraph(sead::DrawContext*, const sead::Camera&, const sead::Projection&,
                             const sead::Viewport&, const Curve3DDrawArg*) const {}
    virtual void saveToXmlDocument(bool) {}
    virtual void loadFromXmlDocument(const sead::SafeString&) {}

    /// The node in the list of the curves of the AttenuationMgr.
    sead::ListNode mListNode;
};
static_assert(sizeof(Curve) == 0x68, "aal::Curve size mismatch");

}  // namespace aal
