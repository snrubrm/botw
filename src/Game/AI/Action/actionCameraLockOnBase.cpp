#include "Game/AI/Action/actionCameraLockOnBase.h"

namespace uking::action {

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

}  // namespace uking::action
