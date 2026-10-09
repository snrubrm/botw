#include "Game/AI/Action/actionCameraWaterfallClimb.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

CameraWaterfallClimb::CameraWaterfallClimb(const InitArg& arg) : CameraAction(arg) {}

CameraWaterfallClimb::~CameraWaterfallClimb() = default;

void CameraWaterfallClimb::m33() {
    _4c = 3;
    _10c = false;
    _94 = 0;
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

// NON_MATCHING: parameter and scalar load scheduling differ.
void CameraWaterfallClimb::sub_710078B134() {
    _f8 = sub_7100924CAC(*mLat_s);
    if (_f8 <= 0.0f)
        _f8 = 0.1f;
    _fc = sead::Mathf::clampMin(*mLng_s, 0.0f);
    if (_fc >= 90.0f)
        _fc = 89.9f;
    _100 = *mRadius_s;
    if (_100 <= 0.0f)
        _100 = 0.01f;
    _104 = *mHeightAllowance_s;
    if (_104 <= 0.0f)
        _104 = 0.01f;
    _108 = sub_7100924D50(*mFovy_s);
    _84 = std::tan(sead::Mathf::deg2rad(_fc)) * _100;
    _88 = std::tan(sead::Mathf::deg2rad(_f8)) * _84;
    const f32 allowance = sead::Mathf::abs(*mHeightAllowance_s);
    _8c = *mManualHeightMin_s < -allowance ? *mManualHeightMin_s : -allowance;
    const f32 upper = *mManualHeightMax_s > _88 ? *mManualHeightMax_s : _88;
    const f32 upper_allowance = sead::Mathf::abs(*mHeightAllowance_s);
    _90 = upper > upper_allowance ? upper : upper_allowance;
}

// NON_MATCHING: state and camera flag loads have different scheduling.
void CameraWaterfallClimb::sub_710078B26C() {
    auto* player = sub_7100926A14();
    if (!player)
        return;
    const s32 previous_state = _4c;
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    if (stick != sead::Vector2f::zero) {
        _4c = 2;
    } else if (_4c != 1 && _4c != 2) {
        if (_4c == 0) {
            if (player->m191())
                _4c = 1;
        } else {
            _4c = player->m191() ? 1 : 0;
        }
    }
    if (previous_state != _4c) {
        if (_4c == 2)
            sub_710078B89C();
        else if (_4c != 1 || !_10c)
            sub_710078B5C0();
    }
    if (auto* camera = getCamera()) {
        if (_4c == 2)
            camera->_860._7f8.set(1);
        else
            camera->_860._7f8.reset(1);
    }
}

// NON_MATCHING: heading field and scalar scheduling differ.
f32 CameraWaterfallClimb::sub_710078B398() {
    auto* camera = getCamera();
    if (!camera)
        return 0.0f;
    const sead::Vector3f delta = camera->_860._0._0 - camera->_860._0._c;
    const f32 heading = angleStuff(sead::Mathf::rad2deg(std::atan2(delta.x, delta.z)));
    if (_4c == 0)
        return heading;
    const auto& matrix = camera->_860._270;
    f32 target = angleStuff(0.0f);
    if (matrix(0, 2) != 0.0f || matrix(2, 2) != 0.0f)
        target = angleStuff(sead::Mathf::rad2deg(std::atan2(-matrix(0, 2), -matrix(2, 2))));
    if (_94 == 0.0f)
        _94 = angleStuff(angleStuff(heading - target)) > angleStuff(0.0f) ? 1.0f : -1.0f;
    return angleStuff(target + _fc * _94);
}

// NON_MATCHING: target, transition and scalar scheduling differ.
void CameraWaterfallClimb::sub_710078B5C0() {
    auto* camera = getCamera();
    if (!camera || !sub_7100926A14())
        return;
    const sead::Vector3f delta = camera->_860._0._0 - camera->_860._0._c;
    sead::Vector3f target = sead::Vector3f::zero;
    if (auto* camera_actor = getCameraActor()) {
        target = camera_actor->_860._2b8;
        f32 height = 0.0f;
        if (sub_71009269F8(target, &height)) {
            target.y = target.y > height + 0.05f ? target.y : height + 0.05f;
        }
        target.y += *mOffsetY_s;
    }
    _50 = target;
    _5c = camera->_860._0._c - target;
    _68 = angleStuff(sead::Mathf::rad2deg(std::atan2(delta.x, delta.z)));
    _6c = angleStuff(0.0f);
    _70 = _88;
    _78 = _84;
    _7c = std::sqrt(delta.x * delta.x + delta.z * delta.z) - _84;
    _74 = delta.y - _88;
    _80 = camera->_860._0._24 - _108;
    bool changed = _5c != sead::Vector3f::zero;
    f32 duration = changed ? std::fmax(_5c.length(), 0.0f) : 0.0f;
    const f32 angle_distance = sub_71009226D8(_6c);
    if (angle_distance > 0.0f) {
        const f32 angle_duration = angle_distance * 0.2f;
        duration = angle_duration > duration ? angle_duration : duration;
        changed = true;
    }
    const f32 radius_distance = sead::Mathf::abs(_7c);
    if (radius_distance > 0.0f) {
        const f32 radius_duration = radius_distance * 0.5f;
        duration = radius_duration > duration ? radius_duration : duration;
        changed = true;
    }
    const f32 fovy_distance = sead::Mathf::abs(_80);
    if (fovy_distance > 0.0f) {
        const f32 fovy_duration = fovy_distance * 0.5f;
        duration = fovy_duration > duration ? fovy_duration : duration;
        changed = true;
    }
    if (changed)
        duration = sead::Mathf::clampMin(duration, 10.0f);
    _98.sub_710079C384(duration, 0.0f);
    _10c = true;
}

// NON_MATCHING: target, transition and scalar scheduling differ.
void CameraWaterfallClimb::sub_710078B89C() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const sead::Vector3f delta = camera->_860._0._0 - camera->_860._0._c;
    sead::Vector3f target = sead::Vector3f::zero;
    if (auto* camera_actor = getCameraActor()) {
        target = camera_actor->_860._2b8;
        f32 height = 0.0f;
        if (sub_71009269F8(target, &height)) {
            target.y = target.y > height + 0.05f ? target.y : height + 0.05f;
        }
        target.y += *mOffsetY_s;
    }
    _50 = target;
    _5c = camera->_860._0._c - target;
    _68 = angleStuff(sead::Mathf::rad2deg(std::atan2(delta.x, delta.z)));
    _6c = angleStuff(0.0f);
    _78 = _84;
    _7c = std::sqrt(delta.x * delta.x + delta.z * delta.z) - _84;
    _70 = sead::Mathf::clamp(delta.y, _8c, _90);
    _74 = delta.y - _70;
    _80 = camera->_860._0._24 - _108;
    f32 duration = _5c != sead::Vector3f::zero ? std::fmax(_5c.length(), 0.0f) : 0.0f;
    const f32 radius_distance = sead::Mathf::abs(_7c);
    if (radius_distance > 0.0f) {
        const f32 radius_duration = radius_distance * 0.5f;
        duration = radius_duration > duration ? radius_duration : duration;
    }
    const f32 fovy_distance = sead::Mathf::abs(_80);
    if (fovy_distance > 0.0f) {
        const f32 fovy_duration = fovy_distance * 0.5f;
        duration = fovy_duration > duration ? fovy_duration : duration;
    }
    _98.sub_710079C384(sead::Mathf::clampMin(duration, 10.0f), 0.0f);
    _10c = true;
}

// NON_MATCHING: state transitions, vector copies and scalar scheduling differ.
void CameraWaterfallClimb::m34() {
    auto* camera = getCamera();
    if (!camera || !sub_7100926A14())
        return;
    auto* vfr = ksys::VFR::instance();
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    sub_710078B134();
    sub_710078B26C();
    _98.sub_710079C408();
    const f32 remaining = 1.0f - _98._18;
    const sead::Vector3f previous_delta = camera->_860._0._0 - camera->_860._0._c;
    f32 heading = angleStuff(sead::Mathf::rad2deg(std::atan2(previous_delta.x, previous_delta.z)));
    if (_4c == 2) {
        f32 change = sub_7100927230() * stick.x * sub_71009272A8();
        if (vfr)
            change *= vfr->getDeltaFrame();
        heading = angleStuff(heading + change);
    } else if (_4c == 1) {
        const f32 target = angleStuff(sub_710078B398());
        const f32 rate = sub_7100791E44(0.05f);
        heading = angleStuff(heading + angleStuff(rate * angleStuff(target - heading)));
    }
    const f32 radius = _78 + sub_7100791E44(0.2f) * (_84 - _78);
    _78 = radius;
    const f32 radius_transition = _7c;
    sead::Vector3f target = sead::Vector3f::zero;
    if (auto* camera_actor = getCameraActor()) {
        target = camera_actor->_860._2b8;
        f32 height = 0.0f;
        if (sub_71009269F8(target, &height)) {
            target.y = target.y > height + 0.05f ? target.y : height + 0.05f;
        }
        target.y += *mOffsetY_s;
    }
    _50 += (target - _50) * sub_7100791E44(0.6f);
    const sead::Vector3f at = _50 + _5c * remaining;
    f32 vertical;
    if (_4c == 1) {
        vertical = previous_delta.y;
        const f32 rise = at.y - camera->_860._0._c.y;
        if (rise > 0.0f) {
            const f32 displaced = vertical - rise;
            vertical = displaced < -_104 ? -_104 : displaced;
        }
    } else {
        if (_4c == 0) {
            _70 += sub_7100791E44(0.2f) * (_88 - _70);
        } else {
            f32 change = sub_7100927228() * stick.y * sub_7100927238() * 0.2f;
            if (vfr)
                change *= vfr->getDeltaFrame();
            _70 += change;
            _70 = sead::Mathf::clamp(_70, _8c, _90);
        }
        vertical = _70 + remaining * _74;
    }
    act::Unk_7100922700 polar(sead::Vector3f::ez);
    polar._0 = radius + remaining * radius_transition;
    polar._8 = heading;
    const sead::Vector3f offset = polar.sub_7100923254();
    camera->_860._0._c = at;
    camera->_860._0._0 = at + sead::Vector3f(offset.x, vertical, offset.z);
    camera->_860._0._24 = _108 + remaining * _80;
    camera->sub_71007953C8();
}

void CameraWaterfallClimb::m36() {
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mLng_s, "Lng");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mHeightAllowance_s, "HeightAllowance");
    getStaticParam(&mManualHeightMin_s, "ManualHeightMin");
    getStaticParam(&mManualHeightMax_s, "ManualHeightMax");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
}

}  // namespace uking::action
