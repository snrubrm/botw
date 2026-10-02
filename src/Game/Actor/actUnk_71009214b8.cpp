#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCameraUtil.h"

namespace uking::act {

Unk_71009214b8::Unk_71009214b8() = default;

void Unk_71009214b8::set(const sead::Vector3f& pos, const sead::Vector3f& at,
                         const sead::Vector3f& up, f32 a24, f32 a28, f32 a2c, f32 a30, f32 a34) {
    _0.set(pos);
    _c.set(at);
    _18.set(up);
    _24 = a24;
    _28 = a28;
    _2c = a2c;
    _30 = a30;
    _34 = a34;
}

bool Unk_71009214b8::sub_7100921818(sead::Matrix34f* out) const {
    sead::Vector3f dir = _c - _0;
    if (dir.normalize() == 0.0f)
        return false;

    if (_18.x == 0.0f && _18.y == 0.0f && _18.z == 0.0f)
        return false;

    sead::Vector3f side;
    side.setCross(_18, dir);
    if (side.normalize() == 0.0f)
        return false;

    sead::Vector3f up;
    up.setCross(dir, side);
    if (up.normalize() == 0.0f)
        return false;

    out->setBase(0, side);
    out->setBase(1, up);
    out->setBase(2, dir);
    out->setTranslation(_0);
    return true;
}

f32 Unk_71009214b8::sub_710092156C(f32 a1, f32 a2, const sead::Vector3f& pos) const {
    sead::Vector3f local = sead::Vector3f::zero;
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    if (sub_7100921818(&mtx)) {
        mtx.setInverse(mtx);
        local.setMul(mtx, pos);
    }

    const f32 depth = local.z - 0.5f;
    f32 z = local.z;
    f32 offset = 0.0f;
    if (depth < _30) {
        offset = _30 - depth;
        z += offset;
    }

    const f32 half_y = _24 * 0.5f;
    const f32 half_x = half_y * _2c;
    const f32 angle_x = half_x * a1;
    const f32 angle_y = half_y * a2;

    f32 dx = 0.0f;
    const f32 tan_x = std::tan(angle_x);
    if (!(tan_x <= 0.0f))
        dx = -(z - sead::Mathf::abs(local.x) / tan_x);
    dx = sead::Mathf::clampMin(dx, 0.0f);

    f32 dy = 0.0f;
    const f32 tan_y = std::tan(angle_y);
    if (!(tan_y <= 0.0f))
        dy = -(z - sead::Mathf::abs(local.y) / tan_y);

    return offset + sead::Mathf::max(dx, dy);
}



bool Unk_71009214b8::sub_7100921710(const sead::Vector3f& pos, sead::Vector3f* out) const {
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    if (!sub_7100921818(&mtx))
        return false;
    mtx.setInverse(mtx);
    *out = pos;
    out->mul(mtx);
    return true;
}

f32 Unk_71009214b8::sub_7100921A24(f32 offset) const {
    const f32 h = _30 * std::tan(_24 * 0.5f);
    const f32 w = h * _2c;
    return std::sqrt(h * h + w * w) + offset;
}

void Unk_71009214b8::sub_7100921A90(sead::Vector3f* out) const {
    sead::Vector3f dir = _c - _0;
    dir.normalize();
    *out = _0 + dir * _30;
}

void Unk_71009214b8::sub_7100921B48(const sead::Vector3f& p) {
    sead::Vector3f dir = p - _0;
    dir.normalize();
    _0 = p + dir * _30;
}

f32 Unk_71009214b8::sub_7100921C04() const {
    const Unk_7100922700 polar(_c - _0);
    return -polar._4;
}

f32 Unk_71009214b8::sub_7100921C50() const {
    const Unk_7100922700 polar(_c - _0);
    return polar._8;
}

f32 Unk_71009214b8::sub_7100921C98() const {
    return _28 * (180.0f / sead::Mathf::pi());
}

// NON_MATCHING: load scheduling (the original loads _24-_34 as pairs of integers up front)
void Unk_71009214b8::sub_7100921CAC(u32* flags) const {
    u32 f = 0;
    if (std::isnan(_0.x) || std::isnan(_0.y) || std::isnan(_0.z))
        f |= 1;
    if (std::isnan(_c.x) || std::isnan(_c.y) || std::isnan(_c.z))
        f |= 2;
    if (std::isnan(_18.x) || std::isnan(_18.y) || std::isnan(_18.z))
        f |= 4;
    if (std::isnan(_24))
        f |= 8;
    if (std::isnan(_28))
        f |= 0x10;
    if (std::isnan(_2c))
        f |= 0x20;
    if (std::isnan(_30))
        f |= 0x40;
    if (std::isnan(_34))
        f |= 0x80;
    if (!(_24 < sead::Mathf::pi() && _24 > 0.0f))
        f |= 0x100;
    if (!(_2c > 0.0f))
        f |= 0x200;
    if (!(_30 > 0.0f))
        f |= 0x400;
    if (!(_34 > 0.0f))
        f |= 0x800;
    if (_0 == _c)
        f |= 0x1000;
    if (flags) {
        if (!(_34 > _30))
            f |= 0x2000;
        *flags = f;
    }
}

}  // namespace uking::act
