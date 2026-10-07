#pragma once

namespace sead {
class Camera;
class PrimitiveDrawer;
class Projection;
}  // namespace sead

namespace aal {

namespace DebugDrawUtil {
/// Sets the camera and the projection of the drawer and resets its model matrix to the identity.
void initializePrimitiveDrawer(sead::PrimitiveDrawer* drawer, const sead::Camera& camera,
                               const sead::Projection& projection);
}  // namespace DebugDrawUtil

}  // namespace aal
