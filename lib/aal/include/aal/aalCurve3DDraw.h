#pragma once

#include "aal/aalCurve.h"

namespace aal {

class CustomCurve;
class RollOffCurve;
class UnitDistanceCurve;

// The three native curve virtual draw methods forward the same six arguments
// to these static helpers. Curve3DDrawArg remains opaque.
class CustomCurve3DDraw {
public:
    static void drawScreenSpaceGraph(const CustomCurve&, sead::DrawContext*, const sead::Camera&,
                                     const sead::Projection&, const sead::Viewport&, const Curve3DDrawArg*);
    static void draw3DGraph(const CustomCurve&, sead::DrawContext*, const sead::Camera&,
                            const sead::Projection&, const sead::Viewport&, const Curve3DDrawArg*);
};

class RollOffCurve3DDraw {
public:
    static void drawScreenSpaceGraph(const RollOffCurve&, sead::DrawContext*, const sead::Camera&,
                                     const sead::Projection&, const sead::Viewport&, const Curve3DDrawArg*);
    static void draw3DGraph(const RollOffCurve&, sead::DrawContext*, const sead::Camera&,
                            const sead::Projection&, const sead::Viewport&, const Curve3DDrawArg*);
};

class UnitDistanceCurve3DDraw {
public:
    static void drawScreenSpaceGraph(const UnitDistanceCurve&, sead::DrawContext*, const sead::Camera&,
                                     const sead::Projection&, const sead::Viewport&, const Curve3DDrawArg*);
    static void draw3DGraph(const UnitDistanceCurve&, sead::DrawContext*, const sead::Camera&,
                            const sead::Projection&, const sead::Viewport&, const Curve3DDrawArg*);
};

}  // namespace aal
