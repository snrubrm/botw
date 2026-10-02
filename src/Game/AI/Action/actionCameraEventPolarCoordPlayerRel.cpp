#include "Game/AI/Action/actionCameraEventPolarCoordPlayerRel.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCameraUtil.h"

namespace uking::action {

CameraEventPolarCoordPlayerRel::CameraEventPolarCoordPlayerRel(const InitArg& arg)
    : CameraEventPolarCoordPlayer(arg) {}

void CameraEventPolarCoordPlayerRel::m46() {
    getDynamicParam_2(&mOtherActor_d, "OtherActor");
    getDynamicParam_2(&mAtCalcMode_d, "AtCalcMode");
    getDynamicParam_2(&mFovyCalcMode_d, "FovyCalcMode");
    getDynamicParam_2(&mReviseMode_d, "ReviseMode");
    getDynamicParam_2(&mActorIgnoringCollision_d, "ActorIgnoringCollision");
    getDynamicParam_2(&mLatOffset_d, "LatOffset");
    getDynamicParam_2(&mLngOffset_d, "LngOffset");
    getDynamicParam_2(&mRadiusOffset_d, "RadiusOffset");
    getDynamicParam_2(&mFovyParam_d, "FovyParam");
    getDynamicParam_2(&mTime_d, "Time");
    getDynamicParam_2(&mReverseOrder_d, "ReverseOrder");
    getDynamicParam(&mActorNameForOtherActor_d, "ActorNameForOtherActor");
    getDynamicParam(&mUniqueNameForOtherActor_d, "UniqueNameForOtherActor");
    getDynamicParam_2(&mAtParam_d, "AtParam");
}

void CameraEventPolarCoordPlayerRel::m47() {
    s32 other = *mOtherActor_d;
    if (!(other >= 0 && other < 4))
        other = -1;
    if (*mOtherActor_d == 1)
        other = -1;
    _1dc = other;

    u32 at_calc_mode = *mAtCalcMode_d;
    if (at_calc_mode > 2)
        at_calc_mode = 3;
    _1e0 = at_calc_mode;

    _1e4 = *mFovyCalcMode_d != 0;

    const u32 revise_mode = *mReviseMode_d;
    _1e8 = revise_mode < 3 ? revise_mode : 1;

    if (_1dc == 3) {
        const int idx = !*mReverseOrder_d;
        _a0[idx] = mActorNameForOtherActor_d;
        _d0[idx] = mUniqueNameForOtherActor_d;
        if (_1e0 == 1) {
            _a0[2] = mActorNameForOtherActor_d;
            _d0[2] = mUniqueNameForOtherActor_d;
        }
    }

    _1f0.sub_710079C384(*mTime_d, 0.0f);
    CameraEventPolarCoordPlayer::m47();
}

void CameraEventPolarCoordPlayerRel::m49() {
    _1f0.sub_710079C408();
    CameraEventPolarCoordPlayer::m49();
}

// NON_MATCHING: the original does not sink the two read-modify-writes of _818 into one
void CameraEventPolarCoordPlayerRel::m50() {
    auto* camera = getCamera();
    if (!camera)
        return;

    switch (_1e8) {
    case 2:
        camera->_860._818 |= 1;
        break;
    case 0:
        camera->_860._818 |= 2;
        break;
    }
}

float CameraEventPolarCoordPlayerRel::m51() {
    return sub_7100924CAC(*mLatOffset_d);
}

float CameraEventPolarCoordPlayerRel::m52() {
    act::Unk_7100922700 polar;
    m56(&polar);
    return angleStuff(*mLngOffset_d + polar._8);
}

float CameraEventPolarCoordPlayerRel::m53() {
    return sub_7100924D40(*mRadiusOffset_d);
}

float CameraEventPolarCoordPlayerRel::m54() {
    f32 fovy = sead::Mathf::deg2rad(*mFovyParam_d);
    if (_1e4 == 0) {
        if (auto* camera = getCameraActor())
            fovy += camera->_860._0._24;
    }
    return sub_7100924D50(fovy);
}

void CameraEventPolarCoordPlayerRel::m55(sead::Vector3f* out) {
    switch (_1e0) {
    case 0:
        *out = *mAtParam_d;
        out->setMul(_148[*mReverseOrder_d], *out);
        break;
    case 1:
        *out = *mAtParam_d;
        out->setMul(_148[!*mReverseOrder_d], *out);
        break;
    case 2:
        if (auto* camera = getCameraActor()) {
            *out = camera->_860._0._c;
            *out += *mAtParam_d;
        }
        break;
    default:
        *out = *mAtParam_d;
        break;
    }
}

bool CameraEventPolarCoordPlayerRel::m57() {
    return *mTime_d <= 0.0f;
}

float CameraEventPolarCoordPlayerRel::m58() {
    return 1.0f - _1f0._18;
}

void CameraEventPolarCoordPlayerRel::m60(sead::Vector3f* out) {
    _148[0].getTranslation(*out);
}

void CameraEventPolarCoordPlayerRel::m61(sead::Vector3f* out) {
    _148[1].getTranslation(*out);
}

int CameraEventPolarCoordPlayerRel::m62(int idx) {
    switch (idx) {
    case 0:
        if (idx == *mReverseOrder_d)
            return 1;
        return _1dc;
    case 1:
        if (idx == *mReverseOrder_d)
            return 1;
        return _1dc;
    case 2:
        if (_1e0 == 0)
            return 1;
        if (_1e0 == 1)
            return _1dc;
        break;
    }
    return -1;
}

int CameraEventPolarCoordPlayerRel::m63() {
    if (*mActorIgnoringCollision_d != 0)
        return -1;
    return !*mReverseOrder_d;
}

bool CameraEventPolarCoordPlayerRel::m64() {
    return false;
}

}  // namespace uking::action
