#pragma once

#include <gfx/seadCamera.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadProjection.h>

namespace sead {
class TextWriter;
}

namespace aal {

// Constructor ba97e8 creates the drawer at0, projection at28 and camera atd8.
// Independent caller bab1e0 destroys those three members in reverse order.
// The drawer's own vptr remains installed: these are composed objects.
class DebugDrawer {
public:
    explicit DebugDrawer(sead::TextWriter* writer);
    void begin(sead::DrawContext* context);
    void end();
    void drawRect(const sead::Vector2f& position, const sead::Vector2f& size,
                  const sead::Color4f& color, bool outline, const sead::Color4f& outlineColor);
    void drawLine(const sead::Vector2f& start, const sead::Vector2f& end,
                  const sead::Color4f& color);
    void drawFilledCircle(const sead::Vector2f& center, f32 radius, const sead::Color4f& color);

private:
    sead::PrimitiveDrawer mDrawer;
    sead::OrthoProjection mProjection;
    sead::LookAtCamera mCamera;
};
static_assert(sizeof(DebugDrawer) == 0x138);

}  // namespace aal
