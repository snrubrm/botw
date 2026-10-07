#include "KingSystem/World/worldWindMgr.h"
#include "KingSystem/World/worldManager.h"
#include <layer/aglRenderer.h>
#include <layer/aglLayer.h>

namespace ksys::world {

// NON_MATCHING: the Vector3 assignment copies components separately instead of the original word/pair copy.
void WindMgr::sub_71010EEBE4(sead::Vector3f* out, const sead::Vector3f* position) {
    if (!(_28 & 8)) {
        sub_71010EEA98(out, position);
        return;
    }
    *out = _34;
}

nn::gfx::ResTextureData* WindMgr::sub_71010EEEE8() {
    if (!(_28 & 0x40))
        return &_20->_1b8;
    return &_98;
}

f32 WindMgr::sub_71010EEF48() const {
    return _20->_8;
}

// NON_MATCHING: the constant load, multiplication schedule and upper clamp differ.
f32 WindMgr::sub_71010EEF04() const {
    // The original constant at 0x710250d250 is 12.0f.
    const f32 strength = _80 * ((_68 / 12.0f) * 15.0f);
    if (strength < 0.0f)
        return 0.0f;
    if (strength > 1.0f)
        return 1.0f;
    return strength;
}

// NON_MATCHING: the inlined strength calculation has the same differences as sub_71010EEF04.
f32 WindMgr::x_0() {
    return _20->sub_71012FF2B0(sub_71010EEF04());
}

// NON_MATCHING: the inlined strength calculation has the same differences as sub_71010EEF04.
f32 WindMgr::x_1() {
    return _20->sub_71012FF268(sub_71010EEF04());
}

// NON_MATCHING: vector component copies and normalization scheduling differ slightly.
void WindMgr::sub_71010EEA98(sead::Vector3f* out, const sead::Vector3f* position) {
    if (_28 & 6) {
        *out = _40;
        out->normalize();
        return;
    }
    if (auto* manager = Manager::instance())
        *out = position ? manager->getWindDirection(*position) : manager->getWindDirection();
    out->normalize();
}

f32 WindMgr::sub_71010EECE8(const sead::Vector3f* position, f32 value) {
    if (_28 & 0x10)
        return sub_71010EECF8(position, value);
    return sub_71010EEC04();
}

// NON_MATCHING: the flag conditions fold into one comparison and share the fallback branch.
f32 WindMgr::sub_71010EEC04() {
    sead::Vector3f position(0.0f, 0.0f, 0.0f);
    if (auto* renderer = agl::lyr::Renderer::instance()) {
        if (auto* layer = renderer->mLayers[1]) {
            if (auto* camera = layer->sub_7100B60CE0())
                camera->getWorldPosByMatrix(&position);
        }
    }
    auto* manager = Manager::instance();
    if ((!manager || manager->mManualWindTimer == 0) && !(_28 & 0x20)) {
        if (_28 & 8)
            return _2c * _80;
    }
    if (_28 & 6)
        return _4c;
    return manager ? manager->getWindSpeed(position) : 0.0f;
}

}  // namespace ksys::world
