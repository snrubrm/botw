#include "KingSystem/World/worldWindMgr.h"
#include "KingSystem/World/worldManager.h"
#include <utility/aglPrimitiveTexture.h>
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

agl::TextureSampler* WindMgr::sub_71010EEE94() {
    if (!(_28 & 0x40))
        return &_20->_48;
    return agl::utl::PrimitiveTexture::instance()->mSamplers[2];
}

agl::TextureData* WindMgr::sub_71010EEEBC() {
    if (!(_28 & 0x40))
        return _20->_40;
    return &agl::utl::PrimitiveTexture::instance()->mSamplers[2]->mTextureData;
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

// NON_MATCHING: flag branches share fallback paths and the blend math is scheduled differently.
f32 WindMgr::sub_71010EECF8(const sead::Vector3f* position, f32 value) {
    sead::Vector3f wind;
    if (_28 & 8)
        wind = _34;
    else
        sub_71010EEA98(&wind, position);
    sead::Vector2f direction(wind.x, wind.z);
    direction.normalize();
    auto* manager = Manager::instance();
    f32 speed;
    if ((!manager || manager->mManualWindTimer == 0) && !(_28 & 0x20) && (_28 & 8))
        speed = _2c * _80;
    else if (_28 & 6)
        speed = _4c;
    else
        speed = manager ? manager->getWindSpeed(*position) : 0.0f;
    const f32 strength = _20->sub_71012FF01C(position, &direction, speed / 15.0f, value);
    const f32 excess = speed - 15.0f;
    // The original upper-bound comparison selects 1 even when excess is NaN.
    const f32 blend = excess < 0.0f ? 0.0f : excess <= 1.0f ? excess : 1.0f;
    return speed * ((strength + (1.0f - strength) * blend) * 0.3f + 0.7f);
}

}  // namespace ksys::world
