#include "aal/aalDebugDrawer.h"

namespace aal {

// 0x7100BA9970
void DebugDrawer::begin(sead::DrawContext* context) {
    mDrawer.setDrawContext(context);
    mDrawer.begin();
}

// 0x7100BA9994
void DebugDrawer::end() {
    mDrawer.end();
}

// 0x7100BA9998
// NON_MATCHING: matrix construction and translation stores use a different schedule.
void DebugDrawer::drawRect(const sead::Vector2f& position, const sead::Vector2f& size,
                           const sead::Color4f& color, bool outline,
                           const sead::Color4f& outlineColor) {
    const sead::Matrix34f* model = mDrawer.getModelMatrix();
    sead::Matrix34f rectangle;
    rectangle.makeIdentity();
    rectangle.scaleBases(size.x, size.y, 0.0f);
    rectangle.setTranslation({position.x + size.x * 0.5f, -(position.y + size.y * 0.5f), 0.0f});
    mDrawer.setModelMatrix(&rectangle);
    mDrawer.drawQuad(color, color);
    if (outline)
        mDrawer.drawBox(outlineColor, outlineColor);
    mDrawer.setModelMatrix(model);
}

// 0x7100BA9A60
void DebugDrawer::drawLine(const sead::Vector2f& start, const sead::Vector2f& end,
                           const sead::Color4f& color) {
    mDrawer.drawLine({start.x, -start.y, 0.0f}, {end.x, -end.y, 0.0f}, color);
}

// 0x7100BA9AB4
void DebugDrawer::drawFilledCircle(const sead::Vector2f& center, f32 radius,
                                   const sead::Color4f& color) {
    mDrawer.drawSphere4x8({center.x, -center.y, 0.0f}, radius, color);
}

}  // namespace aal
