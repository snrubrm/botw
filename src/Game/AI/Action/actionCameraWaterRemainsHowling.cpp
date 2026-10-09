#include "Game/AI/Action/actionCameraWaterRemainsHowling.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>

namespace uking::action {

CameraWaterRemainsHowling::CameraWaterRemainsHowling(const InitArg& arg) : CameraAction(arg) {}

CameraWaterRemainsHowling::~CameraWaterRemainsHowling() = default;

void CameraWaterRemainsHowling::m33() {
    _100 = sub_7100924D40(*mRadius_s);
    _104 = sub_7100924D50(*mFovy_s);
    _108 = sead::Mathf::clamp(_108, 0.0f, 1.0f);
    _10c = 1.0f - _108;
    sub_710078BF18();
    sub_710078C1F0();
    _110 = false;
}

// NON_MATCHING: vector copies and terrain bound scheduling differ.
void CameraWaterRemainsHowling::sub_710078BF18() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const sead::Vector3f origin = camera->_11f0.getTranslation();
    f32 height = 0.0f;
    const bool has_height = sub_71009269F8(origin, &height);
    f32 target_y = camera->_1220.y + *mAtY_s;
    if (has_height) {
        const f32 water_height = height + sead::Mathf::clampMin(*mWaterAvoid4At_s, 0.0f);
        if (target_y < water_height)
            target_y = water_height;
    }
    sead::Vector3f forward = camera->_11f0.getBase(2);
    forward.y = 0.0f;
    const f32 forward_length = forward.length();
    if (forward_length > 0.0f)
        forward *= 1.0f / forward_length;
    const sead::Vector3f target = sead::Vector3f(origin.x, target_y, origin.z) + forward * *mAtOffsetZ_s;
    _64 = target;
    _64.y = camera->_860._2b8.y;
    if (has_height) {
        const f32 water_height = height + sead::Mathf::clampMin(*mWaterAvoid4CameraPos_s, 0.0f);
        if (_64.y < water_height)
            _64.y = water_height;
    }
    sead::Vector3f offset(camera->_860._2b8.x - target.x, 0.0f,
                         camera->_860._2b8.z - target.z);
    const f32 distance = offset.length();
    if (offset.x == 0.0f && offset.z == 0.0f)
        offset = sead::Vector3f::ez;
    const f32 offset_length = offset.length();
    const f32 radius_offset = *mRadiusFromPlayer_s;
    if (offset_length > 0.0f) {
        const f32 desired = distance + radius_offset;
        const f32 radius = _100 < desired ? desired : _100;
        offset *= radius / offset_length;
    }
    _64 += offset;
    const act::Unk_7100922700 polar(target - _64);
    _4c = polar._4;
    _50 = polar._8;
    _54 = 6.0f;
}

// NON_MATCHING: transition field loads and scalar scheduling differ.
void CameraWaterRemainsHowling::sub_710078C1F0() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._c - camera->_860._0._0);
    _70 = angleStuff(polar._4 - _4c);
    f32 duration = 0.0f;
    if (angleStuff(_70) != angleStuff(0.0f))
        duration = sead::Mathf::clampMin(sub_71009226D8(_70) * 0.1f, 0.0f);
    _74 = angleStuff(polar._8 - _50);
    if (angleStuff(_74) != angleStuff(0.0f)) {
        const f32 yaw_duration = sub_71009226D8(_74) * 0.05f;
        duration = duration > yaw_duration ? duration : yaw_duration;
    }
    _78 = polar._0 - _54;
    _88 = camera->_860._0._0 - _64;
    if (_88 != sead::Vector3f::zero) {
        const f32 position_duration = _88.length() * 0.1f;
        duration = duration > position_duration ? duration : position_duration;
    }
    _94 = camera->_860._0._24 - _104;
    if (_94 != 0.0f) {
        const f32 degrees = sead::Mathf::rad2deg(_94);
        const f32 fovy_duration = (degrees > 0.0f ? degrees : -degrees) * 0.25f;
        duration = duration > fovy_duration ? duration : fovy_duration;
    }
    _98 = camera->_860._0._28;
    if (_98 != 0.0f) {
        const f32 degrees = sead::Mathf::rad2deg(_98);
        const f32 roll_duration = (degrees > 0.0f ? degrees : -degrees) * 0.5f;
        duration = duration > roll_duration ? duration : roll_duration;
    }
    _a0.sub_710079C384(duration != 0.0f ? std::fmax(duration, 5.0f) : duration, 0.0f);
    _a0.sub_710079C3F8(*mConnect_s);
}

// NON_MATCHING: polar/vector copies and field-load scheduling differ.
void CameraWaterRemainsHowling::sub_710078C4F8() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const f32 blend = sead::Mathf::clamp(1.0f - _a0._18, 0.0f, 1.0f);
    const sead::Vector3f origin = camera->_11f0.getTranslation();
    f32 height = 0.0f;
    f32 target_y = camera->_860._2b8.y;
    if (sub_71009269F8(origin, &height)) {
        const f32 water_height = height + sead::Mathf::clampMin(*mWaterAvoid4CameraPos_s, 0.0f);
        if (target_y < water_height)
            target_y = water_height;
    }
    _64.y += sub_710092523C(sub_71009251C4(getCameraActor()), 0.4f) * (target_y - _64.y);
    camera->_860._0._0 = _64 + _88 * blend;
    act::Unk_7100922700 polar(sead::Vector3f::ez);
    polar._8 = angleStuff(angleStuff(blend * _74) + _50);
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(angleStuff(blend * _70) + _4c)));
    polar._0 = sub_7100924D40(_54 + blend * _78);
    camera->_860._0._c = camera->_860._0._0 + polar.sub_7100923254();
    camera->_860._0._24 = _104 + blend * _94;
    camera->_860._0._28 = blend * _98;
}

void CameraWaterRemainsHowling::m36() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusFromPlayer_s, "RadiusFromPlayer");
    getStaticParam(&mAtY_s, "AtY");
    getStaticParam(&mAtOffsetZ_s, "AtOffsetZ");
    getStaticParam(&mWaterAvoid4At_s, "WaterAvoid4At");
    getStaticParam(&mWaterAvoid4CameraPos_s, "WaterAvoid4CameraPos");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mConnect_s, "Connect");
}

}  // namespace uking::action
