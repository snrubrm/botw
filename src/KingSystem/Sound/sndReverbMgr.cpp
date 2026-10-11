#include "KingSystem/Sound/sndReverbMgr.h"
#include <prim/seadScopedLock.h>
#include <cstring>
#include <aal/aalDebugDrawUtil.h>
#include <gfx/seadGraphicsContext.h>
#include <gfx/seadPrimitiveRenderer.h>

namespace ksys::snd {

Unk_7101059828::Unk_7101059828() = default;
void Unk_7101059828::draw(sead::PrimitiveDrawer* drawer, bool a, bool b) {}

void Unk_7101059828::sub_7101059848(f32 value) { _8 = value; }
void Unk_7101059828::sub_7101059850(f32 value) { _c = value; }
void Unk_7101059828::sub_7101059858(f32 value) { _10 = value; }
void Unk_7101059828::sub_7101059860(f32 value) { _14 = value; }
void Unk_7101059828::sub_7101059868(f32 value) { _18 = value; }
void Unk_7101059828::sub_7101059870(f32 value) { _1c = value; }
void Unk_7101059828::sub_7101059878(f32 value) { _20 = value; }
void Unk_7101059828::sub_7101059880(s32 value) { _24 = value; }

Unk_7101059888::Unk_7101059888() {
    _8.initOffset(0x28);
}

Unk_7101059888::~Unk_7101059888() {
    auto lock = sead::makeScopedLock(_20);
    _8.clear();
}

void Unk_7101059888::sub_710105999C(sead::Heap* heap) {
    _74 |= 0xc;
}

void Unk_7101059888::sub_7101059B08() {
    std::memset(_60, 0, sizeof(_60));
}

void Unk_7101059888::sub_7101059B14(Unk_7101059828* controller) {
    if (!controller)
        return;
    auto lock = sead::makeScopedLock(_20);
    if (!_8.isNodeLinked(controller))
        _8.pushBack(controller);
}

void Unk_7101059888::sub_7101059B8C(Unk_7101059828* controller) {
    if (!controller)
        return;
    auto lock = sead::makeScopedLock(_20);
    if (_8.isNodeLinked(controller))
        _8.erase(controller);
}

void Unk_7101059888::sub_7101059C00(sead::DrawContext* context, const sead::Camera& camera,
                                  const sead::Projection& projection,
                                  const sead::Viewport& viewport) {
    if (!(_74 & 1))
        return;
    if (_74 & 0x10) {
        sead::GraphicsContext graphics;
        graphics.setCullFace(2);
        graphics.setDepthTestEnable(true);
        graphics.setDepthWriteEnable(true);
        graphics.apply(context);
    }
    sead::PrimitiveDrawer drawer(context);
    aal::DebugDrawUtil::initializePrimitiveDrawer(&drawer, camera, projection);
    auto lock = sead::makeScopedLock(_20);
    for (auto& controller : _8)
        controller.draw(&drawer, (_74 & 4) != 0, (_74 & 8) != 0);
}

}  // namespace ksys::snd
