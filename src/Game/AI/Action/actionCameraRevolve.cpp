#include "Game/AI/Action/actionCameraRevolve.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

CameraRevolve::CameraRevolve(const InitArg& arg) : CameraAction(arg) {}

CameraRevolve::~CameraRevolve() = default;

// NON_MATCHING: polar values, radius clamp and equipment-name lifetimes differ.
void CameraRevolve::m33() {
    auto* player = sub_7100926A14();
    if (!player)
        return;
    const auto& player_transform = player->getMtx();
    f32 yaw = 180.0f;
    if (player_transform(0, 2) != 0.0f || player_transform(2, 2) != 0.0f)
        yaw += sead::Mathf::rad2deg(std::atan2(player_transform(0, 2), player_transform(2, 2)));
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _4c = angleStuff(yaw + *mLngTarget_s);
    _50 = angleStuff(*mIsKeepLng_s ? 0.0f : polar._8 - _4c);
    _54 = *mLngCus_s;
    _58 = 0.0f;
    _5c = -sead::Mathf::pi() * 0.5f;
    _60 = sead::Mathf::deg2rad(*mStartCus_s * 180.0f);
    _64 = sead::Mathf::clamp((camera->_860._0._c - camera->_860._0._0).length(),
                           *mRadiusMin_s, *mRadiusMax_s);
    if (sub_7100926D24()) {
        _68 = *mAtHCus_s;
    } else if (player->_d30 == player->getEquipmentTypeName(1)) {
        _68 = *mAtHCusSword_s;
    } else {
        _68 = *mAtHCus_s;
    }
}

void CameraRevolve::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraRevolve::m36() {
    getStaticParam(&mLatTarget_s, "latTarget");
    getStaticParam(&mLatCus_s, "latCus");
    getStaticParam(&mIsKeepLat_s, "isKeepLat");
    getStaticParam(&mLngTarget_s, "lngTarget");
    getStaticParam(&mLngCus_s, "lngCus");
    getStaticParam(&mIsKeepLng_s, "isKeepLng");
    getStaticParam(&mRadiusMin_s, "radiusMin");
    getStaticParam(&mRadiusMax_s, "radiusMax");
    getStaticParam(&mRadiusCus_s, "radiusCus");
    getStaticParam(&mSideOffset_s, "sideOffset");
    getStaticParam(&mSideOffsetCus_s, "sideOffsetCus");
    getStaticParam(&mWorldBaseOffset_s, "worldBaseOffset");
    getStaticParam(&mPlayerBaseOffset_s, "playerBaseOffset");
    getStaticParam(&mAtHCus_s, "atHCus");
    getStaticParam(&mAtHCusSword_s, "atHCusSword");
    getStaticParam(&mAtVCus_s, "atVCus");
    getStaticParam(&mFovy_s, "fovy");
    getStaticParam(&mFovyCus_s, "fovyCus");
    getStaticParam(&mStartCus_s, "startCus");
}

}  // namespace uking::action
