#include "Game/AI/Action/actionCameraLockOnBase.h"

#include <cmath>
#include <math/seadMathCalcCommon.h>

namespace uking::action {

bool sub_7100786CF4(const u8* flags, u8 mask) {
    return (*flags & mask) != 0;
}

CameraLockOnBase::CameraLockOnBase(const InitArg& arg) : CameraAction(arg) {}

CameraLockOnBase::~CameraLockOnBase() = default;

bool CameraLockOnBase::m32(sead::Heap* heap) {
    _1bc = true;
    return m42(heap);
}

void CameraLockOnBase::m36() {
    getStaticParam(&mDistMin_s, "distMin");
    getStaticParam(&mDistMax_s, "distMax");
    getStaticParam(&mAtOffsetVNear_s, "atOffsetVNear");
    getStaticParam(&mAtOffsetVFar_s, "atOffsetVFar");
    getStaticParam(&mAtCus_s, "atCus");
    getStaticParam(&mAtOffsetCus_s, "atOffsetCus");
    getStaticParam(&mLatOffsetNear_s, "latOffsetNear");
    getStaticParam(&mLatOffsetFar_s, "latOffsetFar");
    getStaticParam(&mLatMin_s, "latMin");
    getStaticParam(&mLatMax_s, "latMax");
    getStaticParam(&mLatVDiffEffect_s, "latVDiffEffect");
    getStaticParam(&mLatCus_s, "latCus");
    getStaticParam(&mLngNear_s, "lngNear");
    getStaticParam(&mLngFar_s, "lngFar");
    getStaticParam(&mLngMax_s, "lngMax");
    getStaticParam(&mLngCus_s, "lngCus");
    getStaticParam(&mRadiusNear_s, "radiusNear");
    getStaticParam(&mRadiusFar_s, "radiusFar");
    getStaticParam(&mRadiusCus_s, "radiusCus");
    getStaticParam(&mFovyNear_s, "fovyNear");
    getStaticParam(&mFovyFar_s, "fovyFar");
    getStaticParam(&mFovyCus_s, "fovyCus");
}

bool CameraLockOnBase::m42(sead::Heap* heap) {
    return true;
}

void CameraLockOnBase::m43() {}

float CameraLockOnBase::m44() {
    return 0.8f;
}

float CameraLockOnBase::m45() {
    return 0.8f;
}

bool CameraLockOnBase::m51() {
    return true;
}

bool CameraLockOnBase::sub_7100786CC0() {
    return m60(_f4);
}

void CameraLockOnBase::m52() {
    _a0 = _88;
}

// NON_MATCHING: load order only (the original loads _a0._14 before polar._8).
void CameraLockOnBase::sub_7100786974(f32* out) {
    if (auto* camera = getCameraActor()) {
        const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        *out = angleStuff(*mLngNear_s + (*mLngFar_s - *mLngNear_s) * _b8);
        const f32 diff = angleStuff(angleStuff(polar._8 - _a0._14));
        if (diff > angleStuff(0.0f))
            *out = angleStuff(-*out);
    }
}

// NON_MATCHING: the dot product is scheduled after the cross-product length.
void CameraLockOnBase::sub_71007860DC(const act::Unk_7100922700* polar, f32* out) {
    f32 base = 0.8f;
    f32 effect = 0.6f;
    if (_a0._0.y > 1.5f) {
        const f32 blend = _a0._0.y >= 3.0f ? 0.2f : ((_a0._0.y - 1.5f) / 1.5f) * 0.2f;
        base -= blend;
        effect = blend * -1.8f + 0.6f;
    }
    const sead::Vector3f direction = polar->sub_7100923254();
    const sead::Vector3f axis = _a0._0;
    sead::Vector3f cross;
    cross.setCross(direction, axis);
    const f32 angle = std::atan2(cross.length(), direction.dot(axis));
    *out = base - effect * ((std::cos(angle) + 1.0f) * -0.5f + 1.0f);
}

// NON_MATCHING: vector copying, stack slots and radius comparisons differ.
void CameraLockOnBase::sub_7100786A44(act::Unk_71009214b8* out, const f32* latitude,
                                    const f32* longitude) {
    sead::Vector3f near = sead::Vector3f::zero;
    sead::Vector3f far = sead::Vector3f::zero;
    if (auto* camera = getCameraActor()) {
        far = camera->_860._2b8;
        near = camera->_860._2ac;
    }
    f32 ratio = 0.5f;
    const act::Unk_7100922700 direction(1.0f, *latitude, *longitude);
    sub_71007860DC(&direction, &ratio);
    out->_c = ratio * _a0._0 + far;
    out->_c.y += *mAtOffsetVNear_s + (*mAtOffsetVFar_s - *mAtOffsetVNear_s) * _b8;
    act::Unk_7100922700 polar(_e4 + (_e8 - _e4) * _b8, *latitude, *longitude);
    out->_0 = polar.sub_7100923254() + out->_c;
    f32 radius = out->sub_710092156C(m44(), m45(), far);
    if (radius <= 0.0f)
        radius = 0.0f;
    f32 adjustment = out->sub_710092156C(m44(), m45(), near);
    if (radius <= adjustment)
        radius = adjustment;
    adjustment = out->sub_710092156C(m44(), m45(), _7c);
    if (radius <= adjustment)
        radius = adjustment;
    polar._0 += radius;
    out->_0 = polar.sub_7100923254() + out->_c;
}

}  // namespace uking::action
