#include "KingSystem/Sound/sndReverbMgr.h"
#include <math/seadMathCalcCommon.h>
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

void Unk_7101059888::sub_71010599AC() {
    auto lock = sead::makeScopedLock(_20);

    f32 v0 = -sead::Mathf::maxNumber();
    f32 v1 = -sead::Mathf::maxNumber();
    f32 v2 = -sead::Mathf::maxNumber();
    f32 v3 = -sead::Mathf::maxNumber();
    f32 v4 = -sead::Mathf::maxNumber();

    for (auto& controller : _8) {
        if (controller._24 > 0) {
            --controller._24;
            const bool useArea = (_74 & 0x20) != 0;
            const f32 scale = controller._20;
            v0 = sead::Mathf::max(scale * (useArea ? _78[0] : controller._8), v0);
            v1 = sead::Mathf::max(scale * (useArea ? _78[1] : controller._c), v1);
            v2 = sead::Mathf::max(scale * (useArea ? _78[2] : controller._10), v2);
            v3 = sead::Mathf::max(scale * (useArea ? _78[3] : controller._14), v3);
            v4 = sead::Mathf::max(scale * (useArea ? _78[4] : controller._18), v4);
        }
    }

    _60[0] = sead::Mathf::max(0.0f, v0);
    _60[1] = sead::Mathf::max(0.0f, v1);
    _60[2] = sead::Mathf::max(0.0f, v2);
    _60[3] = sead::Mathf::max(0.0f, v3);
    _60[4] = sead::Mathf::max(0.0f, v4);
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
