#include <cmath>
#include <gfx/seadViewport.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/VFR.h"

void sub_7100924BE4(ksys::act::ActorConstDataAccess* accessor) {
    if (auto* info = ksys::act::PlayerInfo::instance())
        ksys::act::acquireActor(&info->getPlayerLink(), accessor);
}

f32 sub_7100924C08(f32 fovy, f32 aspect) {
    return 2 * std::atan2(std::tan(fovy * 0.5f) * aspect, 1.0f);
}

// NON_MATCHING: scheduling (the original loads `in` before the multiplications)
void sub_7100924C40(sead::Vector2f* out, const sead::Vector2f& in) {
    const auto* viewport = sub_710092DAD0();
    if (!viewport)
        return;
    const f32 half_w = viewport->getSizeX() * 0.5f;
    const f32 half_h = viewport->getSizeY() * 0.5f;
    out->set(in.x * half_w, in.y * half_h);
}

void sub_7100924C94(f32 a, f32 b, f32* min, f32* max) {
    *min = a < b ? a : b;
    *max = a > b ? a : b;
}

f32 sub_7100924CAC(f32 value) {
    return sead::Mathf::clamp(value, -89.9f, 89.9f);
}

void sub_7100924CDC(f32 a, f32 b, f32* min, f32* max) {
    sub_7100924C94(sub_7100924CAC(a), sub_7100924CAC(b), min, max);
}

f32 sub_7100924D40(f32 value) {
    return sead::Mathf::clampMin(value, 0.01f);
}

f32 sub_7100924D50(f32 value) {
    return sead::Mathf::clamp(value, sead::Mathf::deg2rad(0.1f), sead::Mathf::deg2rad(179.9f));
}

f32 sub_7100924D80(f32 value) {
    return sead::Mathf::clamp(value, 0.0f, 1.0f);
}

void sub_7100924DA4(f32 a, f32 b, f32* min, f32* max) {
    sub_7100924C94(sub_7100924D80(a), sub_7100924D80(b), min, max);
}

f32 sub_7100924DFC(f32 deg) {
    while (deg < -180.0f)
        deg += 360.0f;
    while (deg > 180.0f)
        deg -= 360.0f;
    return deg;
}

bool sub_7100924E48(const sead::Vector3f& dir, const f32& scale, sead::Vector3f* out) {
    if (dir.x == 0.0f && dir.z == 0.0f)
        return false;
    sead::Vector3f v(dir.x, 0.0f, dir.z);
    v.normalize();
    out->x = v.z;
    out->y = 0.0f;
    out->z = -v.x;
    out->multScalar(scale);
    return true;
}


f32 sub_7100924F04() {
    return sub_71009222E8();
}

bool sub_7100925110(const sead::Matrix33f& mtx, int axis) {
    if (u32(axis) > 2)
        return false;
    sead::Vector3f v;
    mtx.getBase(v, axis);
    if (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f)
        return false;
    const f32 h = std::sqrt(v.x * v.x + v.z * v.z);
    if (h == 0.0f)
        return false;
    return std::atan2(sead::Mathf::abs(v.y), h) * (180.0f / sead::Mathf::pi()) < 60.0f;
}

f32 sub_71009251C4(const uking::act::Camera* camera) {
    if (camera)
        return camera->Unk_7102459cc0::_8;
    auto* vfr = ksys::VFR::instance();
    if (!vfr)
        return 1.0f;
    return vfr->getDeltaFrame();
}

f32 sub_710092523C(f32 exponent, f32 t) {
    return 1.0f - std::pow(1.0f - t, exponent);
}
