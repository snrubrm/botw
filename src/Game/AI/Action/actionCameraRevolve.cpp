#include "Game/AI/Action/actionCameraRevolve.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/System/VFR.h"

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

// NON_MATCHING: polar snapshots, rotation and smoothing value scheduling differ.
void CameraRevolve::m34() {
    auto* player = sub_7100926A14();
    if (!player)
        return;
    ksys::act::Actor* subject = player;
    if (sub_7100926D24()) {
        subject = sead::DynamicCast<ksys::act::Actor>(
            ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr));
        if (!subject)
            return;
    }
    const auto& subject_transform = subject->getMtx();
    const f32 forward_x = subject_transform(0, 2);
    const f32 forward_z = subject_transform(2, 2);
    sead::Vector3f subject_position;
    subject_transform.getTranslation(subject_position);
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 initial(camera->_860._0._0 - camera->_860._0._c);
    act::Unk_7100922700 polar = initial;
    sead::Mathf::chase(&_5c, sead::Mathf::pi() * 0.5f,
                      _60 * ksys::VFR::instance()->getDeltaFrame());
    _58 = (std::sin(_5c) + 1.0f) * 0.5f;
    bool latitude_pending = false;
    if (!*mIsKeepLat_s) {
        const f32 rate = ksys::VFR::getLerpFactor(*mLatCus_s);
        const f32 latitude = angleStuff(initial._4 + rate * (*mLatTarget_s - initial._4));
        polar._4 = angleStuff(initial._4 + angleStuff(latitude - initial._4) * _58);
        const f32 difference = angleStuff(angleStuff(*mLatTarget_s) - polar._4);
        latitude_pending = !(difference <= 0.1f) || difference < -0.1f;
    }
    bool longitude_pending = false;
    if (!*mIsKeepLng_s) {
        f32 yaw = angleStuff(0);
        if (forward_x != 0.0f || forward_z != 0.0f)
            yaw = angleStuff(sead::Mathf::rad2deg(std::atan2(forward_x, forward_z) + sead::Mathf::pi()));
        const f32 target = angleStuff(yaw + *mLngTarget_s);
        const f32 difference = angleStuff(target - _4c);
        const f32 rate = sub_7100791E44(*mLngCus_s + (1.0f - *mLngCus_s) * _58);
        _4c = angleStuff(_4c + difference * rate);
        polar._8 = angleStuff(angleStuff(_50 * (1.0f - _58)) + _4c);
        const f32 remaining = angleStuff(target - polar._8);
        longitude_pending = !(remaining <= 0.1f) || remaining < -0.1f;
    }
    if (!latitude_pending && !longitude_pending)
        setFinished();

    const f32 camera_distance =
        (camera->_860._0._0 - sub_7100928868(camera->_860._164)).length();
    sead::Vector3f player_position;
    player->getMtx().getTranslation(player_position);
    const f32 player_distance = (camera->_860._0._0 - player_position).length();
    f32 radius = initial._0 + (player_distance - camera_distance);
    if (radius < *mRadiusMin_s)
        radius = *mRadiusMin_s;
    else if (radius > *mRadiusMax_s)
        radius = *mRadiusMax_s;
    const f32 distance_rate = sub_7100791E44(0.2f);
    _64 += _58 * (distance_rate * (radius - _64));
    const f32 radius_rate = sub_7100791E44(*mRadiusCus_s);
    polar._0 = initial._0 + _58 * (radius_rate * (_64 - initial._0));

    const sead::Vector3f previous_player_position = player->getPreviousPos();
    sead::Vector3f target = sub_7100926D24() ? subject_position : previous_player_position;
    target += *mWorldBaseOffset_s;
    sead::Vector3f side(*mSideOffset_s * camera->_860._18c, 0.0f, 0.0f);
    sead::Matrix33f rotation;
    rotation.makeR({sead::Mathf::deg2rad(polar._4), sead::Mathf::deg2rad(polar._8), 0.0f});
    side.rotate(rotation);
    target += side;
    sead::Vector3f player_offset = *mPlayerBaseOffset_s;
    player_offset.rotate(player->getMtx());
    target += player_offset;

    f32 horizontal = *mAtHCus_s;
    if (sub_7100926D24() && player->_d30 == player->getEquipmentTypeName(1) &&
        player->_cfc.isOnBit(0) &&
        (!player->getRootAi() || !player->getRootAi()->isCurrentAction("移動"))) {
        const f32 distance = (target - camera->_860._0._c).length();
        f32 blend = 1.0f;
        if (distance <= 0.8f) {
            blend = 0.0f;
        } else if (!(distance >= 1.5f)) {
            blend = (std::sin((distance - 0.8f) / 0.7f * sead::Mathf::pi() -
                              sead::Mathf::pi() * 0.5f) + 1.0f) * 0.5f;
            if (blend < 0.0f)
                blend = 0.0f;
            else if (blend > 1.0f)
                blend = 1.0f;
        }
        horizontal = *mAtHCusSword_s + blend * (*mAtHCus_s - *mAtHCusSword_s);
    }
    const f32 horizontal_rate = sub_7100791E44(0.6f);
    _68 += _58 * (horizontal_rate * (horizontal - _68));
    const f32 target_horizontal_rate = sub_7100791E44(_68);
    const f32 target_vertical_rate = sub_7100791E44(*mAtVCus_s);
    camera->_860._0._c.x += _58 * (target_horizontal_rate * (target.x - camera->_860._0._c.x));
    camera->_860._0._c.y += _58 * (target_vertical_rate * (target.y - camera->_860._0._c.y));
    camera->_860._0._c.z += _58 * (target_horizontal_rate * (target.z - camera->_860._0._c.z));
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    const f32 fovy = sead::Mathf::deg2rad(*mFovy_s);
    const f32 fovy_rate = sub_7100791E44(*mFovyCus_s);
    camera->_860._0._24 += _58 * (fovy_rate * (fovy - camera->_860._0._24));
    camera->sub_71007953C8();
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
