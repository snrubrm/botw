#include "aal/aalCurve3DDraw.h"

namespace aal {

void CustomCurve3DDraw::drawScreenSpaceGraph(const CustomCurve& curve, sead::DrawContext* context,
                                            const sead::Camera& camera, const sead::Projection& projection,
                                            const sead::Viewport& viewport, const Curve3DDrawArg* arg) {
    draw3DGraph(curve, context, camera, projection, viewport, arg);
}

void RollOffCurve3DDraw::drawScreenSpaceGraph(const RollOffCurve& curve, sead::DrawContext* context,
                                             const sead::Camera& camera, const sead::Projection& projection,
                                             const sead::Viewport& viewport, const Curve3DDrawArg* arg) {
    draw3DGraph(curve, context, camera, projection, viewport, arg);
}

void UnitDistanceCurve3DDraw::drawScreenSpaceGraph(const UnitDistanceCurve& curve, sead::DrawContext* context,
                                                  const sead::Camera& camera, const sead::Projection& projection,
                                                  const sead::Viewport& viewport, const Curve3DDrawArg* arg) {
    draw3DGraph(curve, context, camera, projection, viewport, arg);
}

}  // namespace aal
