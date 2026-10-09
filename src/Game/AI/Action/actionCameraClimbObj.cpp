#include "Game/AI/Action/actionCameraClimbObj.h"
#include <cfloat>
#include <cmath>
#include "KingSystem/System/Timer.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCamera.h"

namespace uking::action {

CameraClimbObj::CameraClimbObj(const InitArg& arg) : CameraAction(arg) {}

CameraClimbObj::~CameraClimbObj() = default;

bool CameraClimbObj::m32(sead::Heap* heap) {
    return true;
}

void CameraClimbObj::m35() {
    if (auto* camera = getCamera())
        camera->_860._7fc.sub_710079B62C(0x200000);
}

// NON_MATCHING: scheduling only (the original stores _64 after computing the new y and uses another register for the
// offset sum).
void CameraClimbObj::m33() {
    _110 = sub_7100924CAC(*mLat_s);
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_114, &_118);
    _11c = sub_7100924D40(*mRadius_s);
    _120 = sub_7100924D50(*mFovy_s);
    _124 = 0;
    _125 = 3;

    if (auto* camera = getCamera())
        _74 = camera->_860._48c;

    f32 offset;
    if (auto* camera = getCameraActor()) {
        const f32 dy = camera->_860._2b8.y - camera->_860._48c.y;
        offset = dy * (dy <= 0.0f ? 1.0f : 0.75f);
    } else {
        offset = 0.0f;
    }

    _68 = _74;
    _80 = offset;
    _68.y = offset + (_68.y + *mOffsetY_s);
    _64 = FLT_MAX;
}

void CameraClimbObj::sub_7100755C80() {
    if (auto* camera = getCamera()) {
        const sead::Vector3f d = camera->_860._2b8 - camera->_860._48c;
        if (d.x != 0.0f || d.z != 0.0f) {
            _c8 = act::Unk_7100922700(d)._8;
        } else if (!(_124 & 1)) {
            _c8 = act::Unk_7100922700(camera->_860._0._0 - camera->_860._0._c)._8;
        }
        _124 |= 1;
    }
}

// NON_MATCHING: the final fadd has its operands swapped (s0 + s1 instead of s1 + s0).
void CameraClimbObj::sub_7100755D60() {
    if (auto* camera = getCamera())
        _74 = camera->_860._48c;

    f32 offset;
    if (auto* camera = getCameraActor()) {
        const f32 dy = camera->_860._2b8.y - camera->_860._48c.y;
        offset = dy * (dy <= 0.0f ? 1.0f : 0.75f);
    } else {
        offset = 0.0f;
    }

    const f32 rate = sub_710092523C(sub_71009251C4(getCamera()), 0.6f);
    _68 = _74;
    _80 += rate * (offset - _80);
    _68.y = _80 + (*mOffsetY_s + _74.y);
}

// NON_MATCHING: state/scalar scheduling, clamp branches and vector copies differ.
void CameraClimbObj::m34() {
    _110 = sub_7100924CAC(*mLat_s);
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_114, &_118);
    _11c = sub_7100924D40(*mRadius_s);
    _120 = sub_7100924D50(*mFovy_s);
    auto* camera = getCamera();
    if (!camera)
        return;
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    sub_7100755C80();
    sub_7100755D60();
    const u8 previous_state = _125;
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    if (stick.x != 0.0f || stick.y != 0.0f) {
        _125 = 2;
    } else if (sub_7100927110()) {
        _125 = 0;
    } else if (_125 != 1 && _125 != 2) {
        if (_125 != 0)
            _125 = 0;
        else if (_a8._18 >= 1.0f)
            _125 = 1;
    }
    if (previous_state != _125) {
        switch (_125) {
        case 0:
            sub_7100755F70();
            break;
        case 1:
            sub_7100756190();
            break;
        case 2:
            sub_71007563AC();
            break;
        }
    }
    _a8.sub_710079C408();
    const f32 remaining = 1.0f - _a8._18;
    stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    f32 frame = 0.0f;
    ksys::Timer::update(&frame, 1.0f);
    if (_125 < 2) {
        _84 = angleStuff(_110);
    } else if (_125 == 2) {
        _84 = angleStuff(_84 + frame * (sub_7100927228() * sub_7100927238() *
                                       *mLatStickScale_s * stick.y));
        f32 latitude = _84;
        if (latitude < _114)
            latitude = _114;
        else if (latitude > _118)
            latitude = _118;
        _84 = angleStuff(latitude);
    }
    polar._4 = angleStuff(sub_7100924CAC(angleStuff(angleStuff(remaining * _88) + _84)));
    if (_125 < 2) {
        const f32 rate = sub_7100791E44(sub_7100922390());
        _8c = angleStuff(_8c + angleStuff(rate * angleStuff(_c8 - _8c)));
    } else if (_125 == 2) {
        _8c = angleStuff(_8c + frame * (sub_7100927230() * sub_71009272A8() *
                                       *mLngStickScale_s * stick.x));
    }
    polar._8 = angleStuff(angleStuff(remaining * _90) + _8c);
    _94 = _11c;
    if (camera->_860._498 > 0.0f)
        _94 *= camera->_860._498 * 0.33333334f;
    polar._0 = sub_7100924D40(_94 + remaining * _98);
    _4c += sub_7100791E44(sub_710092239C()) * (_68 - _4c);
    sead::Vector3f offset = _58 * remaining;
    if (_64 < offset.length()) {
        const f32 length = offset.length();
        if (length > 0.0f)
            offset *= _64 / length;
    }
    camera->_860._0._c = _4c + offset;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    _9c = _120;
    camera->_860._0._24 = sub_7100924D50(_120 + remaining * _a0);
    camera->sub_71007953C8();
}

void CameraClimbObj::m36() {
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
}

// NON_MATCHING: prepared-field loads, polar/vector copies and float scheduling differ.
void CameraClimbObj::sub_7100755F70() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _84 = angleStuff(_110);
    _88 = angleStuff(polar._4 - _84);
    f32 duration;
    if (sub_71009226D8(_88) > 0.0f)
        duration = std::fmax(sub_71009226D8(_88), 0.0f);
    else
        duration = 0.0f;
    _8c = _c8;
    _90 = angleStuff(polar._8 - _8c);
    if (sub_71009226D8(_90) > 0.0f) {
        const f32 yaw_duration = sub_71009226D8(_90) * 0.2f;
        if (yaw_duration > duration)
            duration = yaw_duration;
    }
    _94 = _11c;
    if (camera->_860._498 > 0.0f)
        _94 *= camera->_860._498 * 0.33333334f;
    _98 = polar._0 - _94;
    const f32 radius_distance = _98 > 0.0f ? _98 : -_98;
    if (radius_distance > 0.0f && radius_distance * 1.5f > duration)
        duration = radius_distance * 1.5f;
    _4c = _68;
    _58 = camera->_860._0._c - _68;
    const f32 target_distance = _58.length();
    if (target_distance > 0.0f && target_distance * 2.0f > duration)
        duration = target_distance * 2.0f;
    _9c = _120;
    _a0 = camera->_860._0._24 - _120;
    const f32 fov_distance = _a0 > 0.0f ? _a0 : -_a0;
    if (fov_distance > duration && fov_distance > 0.0f)
        duration = fov_distance;
    duration = sead::Mathf::clampMax(duration, 10.0f);
    _a8.sub_710079C384(duration, 0.0f);
}

// NON_MATCHING: prepared-field loads, polar/vector copies and float scheduling differ.
void CameraClimbObj::sub_7100756190() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _84 = angleStuff(_110);
    _88 = angleStuff(polar._4 - _84);
    f32 duration;
    if (sub_71009226D8(_88) > 0.0f)
        duration = std::fmax(sub_71009226D8(_88), 0.0f);
    else
        duration = 0.0f;
    _8c = _c8;
    _90 = angleStuff(polar._8 - _8c);
    if (sub_71009226D8(_90) > 0.0f) {
        const f32 yaw_duration = sub_71009226D8(_90) * 0.2f;
        if (yaw_duration > duration)
            duration = yaw_duration;
    }
    _94 = _11c;
    if (camera->_860._498 > 0.0f)
        _94 *= camera->_860._498 * 0.33333334f;
    _98 = polar._0 - _94;
    const f32 radius_distance = _98 > 0.0f ? _98 : -_98;
    if (radius_distance > 0.0f && radius_distance * 1.5f > duration)
        duration = radius_distance * 1.5f;
    _4c = _68;
    _58 = camera->_860._0._c - _68;
    const f32 target_distance = _58.length();
    if (target_distance > 0.0f && target_distance * 2.0f > duration)
        duration = target_distance * 2.0f;
    _9c = _120;
    _a0 = camera->_860._0._24 - _120;
    const f32 fov_distance = _a0 > 0.0f ? _a0 : -_a0;
    if (fov_distance > duration && fov_distance > 0.0f)
        duration = fov_distance;

    _a8.sub_710079C384(duration, 0.0f);
}

// NON_MATCHING: prepared-field loads, polar/vector copies and float scheduling differ.
void CameraClimbObj::sub_71007563AC() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 latitude = polar._4;
    if (latitude < _114)
        latitude = _114;
    else if (latitude > _118)
        latitude = _118;
    _84 = angleStuff(latitude);
    _88 = angleStuff(polar._4 - _84);
    f32 duration;
    if (sub_71009226D8(_88) > 0.0f)
        duration = std::fmax(sub_71009226D8(_88), 0.0f);
    else
        duration = 0.0f;
    _8c = polar._8;
    _90 = angleStuff(polar._8 - _8c);
    if (sub_71009226D8(_90) > 0.0f) {
        const f32 yaw_duration = sub_71009226D8(_90) * 0.2f;
        if (yaw_duration > duration)
            duration = yaw_duration;
    }
    _94 = _11c;
    if (camera->_860._498 > 0.0f)
        _94 *= camera->_860._498 * 0.33333334f;
    _98 = polar._0 - _94;
    const f32 radius_distance = _98 > 0.0f ? _98 : -_98;
    if (radius_distance > 0.0f && radius_distance * 1.5f > duration)
        duration = radius_distance * 1.5f;
    _4c = _68;
    _58 = camera->_860._0._c - _68;
    const f32 target_distance = _58.length();
    if (target_distance > 0.0f && target_distance * 2.0f > duration)
        duration = target_distance * 2.0f;
    _9c = _120;
    _a0 = camera->_860._0._24 - _120;
    const f32 fov_distance = _a0 > 0.0f ? _a0 : -_a0;
    if (fov_distance > duration && fov_distance > 0.0f)
        duration = fov_distance;

    _a8.sub_710079C384(duration, 0.0f);
}

}  // namespace uking::action
