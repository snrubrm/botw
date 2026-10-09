#include "Game/AI/Action/actionCameraLockOnAimingAt.h"
#include <cmath>
#include <math/seadQuat.h>
#include <gfx/seadViewport.h>
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/Utils/MathUtil.h"

const sead::Vector2f& sub_7100A9B928();
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraLockOnAimingAt::CameraLockOnAimingAt(const InitArg& arg) : CameraAction(arg) {}

CameraLockOnAimingAt::~CameraLockOnAimingAt() = default;

void CameraLockOnAimingAt::m33() {
    _4c.sub_71008A4644();
    _128.reset();
    _138.set(0, 0, 0);
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

// NON_MATCHING: camera state, angle and transition scheduling differ.
void CameraLockOnAimingAt::m34() {
    auto* camera = getCamera();
    auto* attention = ksys::act::Attention::instance();
    if (!camera || !attention)
        return;
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    sub_7100924CDC(sub_7100924CAC(*mLatMin_s), sub_7100924CAC(*mLatMax_s), &_15c, &_160);
    const bool attention_changed = attention->sub_7100D75490();
    bool changed;
    {
        ksys::act::BaseProcLink target;
        if (auto* current_attention = ksys::act::Attention::instance())
            current_attention->sub_7100D74148(&target);
        changed = !(_128 == target);
        _128 = target;
    }
    sub_71007744A8(changed);
    sub_71007748EC();
    if (_128.hasProc()) {
        if (auto* current_camera = getCamera()) {
            if (!ksys::util::sub_71011F1040(current_camera->_860._318)) {
                _150 = current_camera->_860._318;
            } else {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&_128, &accessor);
            }
        }
    }
    sub_71007749F8();
    sub_7100774AF4();
    sub_7100774CB4();
    const bool reset = attention_changed || changed;
    sub_7100774DEC(reset);
    if (reset)
        sub_7100775000();
    const f32 progress = _1c0._18;
    _1c0.sub_710079C408();
    const f32 remaining = 1.0f - _1c0._18;
    if (progress < 1.0f && _1c0._18 >= 1.0f)
        sub_710074BCB4();
    const f32 position_rate = sub_7100791E44(0.6f);
    _1a0 += (_16c - _1a0) * position_rate;
    camera->_860._0._c = _1a0 + _1ac * remaining;
    const f32 longitude_rate = sub_7100791E44(0.6f);
    _17c = angleStuff(_17c + longitude_rate * angleStuff(angleStuff(_18c + _168) - _17c));
    polar._8 = angleStuff(angleStuff(remaining * _184) + _17c);
    const f32 latitude_rate = sub_7100791E44(0.6f);
    const f32 latitude = angleStuff(sead::Mathf::clamp(angleStuff(_188 + _164), _15c, _160));
    _178 = angleStuff(angleStuff(latitude_rate * angleStuff(latitude - _178)) + _178);
    polar._4 = angleStuff(angleStuff(remaining * _180) + _178);
    polar._4 = angleStuff(sead::Mathf::clamp(polar._4, _15c, _160));
    polar._0 = *mRadius_s + remaining * _1b8;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->_860._0._24 = *mFovy_s + remaining * _1bc;
    camera->_860.sub_710079BD5C();
    camera->sub_71007953C8();
}

void CameraLockOnAimingAt::m36() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mInputRangeNearDist_s, "InputRangeNearDist");
    getStaticParam(&mLatInputRange_s, "LatInputRange");
    getStaticParam(&mLngInputRange_s, "LngInputRange");
    getStaticParam(&mInputRangeFarDist_s, "InputRangeFarDist");
    getStaticParam(&mLatInputRangeFar_s, "LatInputRangeFar");
    getStaticParam(&mLngInputRangeFar_s, "LngInputRangeFar");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetX_s, "OffsetX");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mGyro_s, "Gyro");
}

void CameraLockOnAimingAt::sub_71007749F8() {
    const f32 dist = std::sqrt((_144.x - _150.x) * (_144.x - _150.x) +
                               (_144.z - _150.z) * (_144.z - _150.z));
    f32 ratio;
    if (dist == 0.0f)
        ratio = 1.0f;
    else
        ratio = sead::Mathf::clamp(*mOffsetX_s / dist, -1.0f, 1.0f);
    const f32 angle = std::asin(ratio);
    const act::Unk_7100922700 polar(_144 - _150);
    _168 = angleStuff(sead::Mathf::rad2deg(angle) + polar._8);
}

void CameraLockOnAimingAt::sub_7100775368(ksys::act::BaseProcLink* link) {
    ksys::act::BaseProc* target = sub_7100926A14();
    if (!target)
        return;

    if (sub_7100926D24()) {
        auto* proc = ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr);
        if (sead::IsDerivedFrom<ksys::act::Actor>(proc))
            link->acquire(proc, false);
        else
            link->acquire(target, false);
    } else {
        link->acquire(target, false);
    }
}

// NON_MATCHING: rotation scheduling and the native radius cancellation differ for non-finite input.
void CameraLockOnAimingAt::sub_71007744A8(bool reset) {
    const auto* camera = getCamera();
    if (!camera)
        return;
    sead::Vector3f target = camera->_860._30c - camera->_860._2d0.getTranslation();
    if (reset) {
        _138 = target;
        return;
    }
    // The native call remains even though radius smoothing cancels its delta.
    sub_7100791E44(0.5f);
    const f32 old_length = _138.length();
    const f32 target_length = target.length();
    if (old_length == 0) {
        if (target_length != 0)
            _138 = target;
    } else if (target_length != 0) {
        _138 *= 1.0f / old_length;
        target *= 1.0f / target_length;
        sead::Vector3f axis;
        axis.setCross(_138, target);
        const f32 angle = std::atan2(axis.length(), target.dot(_138));
        const f32 dot = target.dot(_138);
        sead::Quatf rotation;
        if (dot + 1.0f <= sead::Mathf::epsilon()) {
            rotation.makeUnit();
        } else {
            const f32 half_angle = angle * 0.5f;
            const f32 cos_angle = std::cos(half_angle);
            f32 scale;
            f32 w;
            if (cos_angle > dot) {
                const f32 length = std::sqrt(2.0f * (cos_angle + 1.0f));
                w = length * 0.5f;
                scale = (1.0f / length) * (std::sin(half_angle) / std::sqrt(1.0f - dot * dot));
            } else {
                const f32 length = std::sqrt(2.0f * (dot + 1.0f));
                w = length * 0.5f;
                scale = 1.0f / length;
            }
            rotation.set(w, axis.x * scale, axis.y * scale, axis.z * scale);
        }
        _138.rotate(rotation);
    }
    const f32 length = _138.length();
    if (length > 0)
        _138 *= old_length / length;
}

void CameraLockOnAimingAt::sub_71007748EC() {
    ksys::act::BaseProcLink link;
    sub_7100775368(&link);
    if (!link.hasProc())
        return;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
    if (!actor)
        return;
    if (link.hasProcById(sub_7100926A14()))
        _144 = actor->getPreviousPos();
    else
        actor->getMtx().getTranslation(_144);
}

// NON_MATCHING: zero-vector load and scalar scheduling differ.
void CameraLockOnAimingAt::sub_7100774AF4() {
    _16c = _144;
    _16c.y += *mOffsetY_s;
    auto* proc = ksys::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr, nullptr);
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
        ksys::act::ActorConstDataAccess accessor(actor);
        if (sub_7100926DF0(accessor) || sub_7100926E7C(accessor))
            _16c.y += sub_71009221D4();
        else if (accessor.hasTag(0xffb635e5))
            _16c.y += sub_71009221DC();
    }
    const f32 angle = sead::Mathf::deg2rad(angleStuff(_168 + 90.0f));
    sead::Vector3f offset = sead::Vector3f::zero;
    offset.x = std::sin(angle);
    offset.z = std::cos(angle);
    _16c += offset * *mOffsetX_s;
}

// NON_MATCHING: range interpolation branches and scalar scheduling differ.
void CameraLockOnAimingAt::sub_710077544C() {
    f32 rate;
    if (*mInputRangeNearDist_s == *mInputRangeFarDist_s) {
        rate = 0.5f;
    } else {
        const sead::Vector3f delta(_144.x - _150.x, _144.y + *mOffsetY_s - _150.y,
                                   _144.z - _150.z);
        rate = sead::Mathf::clamp((delta.length() - *mInputRangeNearDist_s) /
                                    (*mInputRangeFarDist_s - *mInputRangeNearDist_s), 0.0f, 1.0f);
    }
    const f32 lat_near = *mLatInputRange_s > 0 ? *mLatInputRange_s : -*mLatInputRange_s;
    const f32 lat_far = *mLatInputRangeFar_s > 0 ? *mLatInputRangeFar_s : -*mLatInputRangeFar_s;
    const f32 lng_near = *mLngInputRange_s > 0 ? *mLngInputRange_s : -*mLngInputRange_s;
    const f32 lng_far = *mLngInputRangeFar_s > 0 ? *mLngInputRangeFar_s : -*mLngInputRangeFar_s;
    _194 = lat_near + rate * (lat_far - lat_near);
    _190 = -_194;
    _19c = lng_near + rate * (lng_far - lng_near);
    _198 = -_19c;
}

// NON_MATCHING: polar elevation load scheduling differs.
void CameraLockOnAimingAt::sub_7100774CB4() {
    const auto* viewport = sub_710092DAB8();
    if (!viewport)
        return;
    const f32 half_height = viewport->getSizeY() * 0.5f;
    if (half_height == 0)
        return;
    const act::Unk_7100922700 polar(_16c - _150);
    if (polar._0 == 0)
        return;
    const f32 ratio = ((sub_7100A9B928().y / half_height) *
                       (std::tan(*mFovy_s * 0.5f) * (*mRadius_s + polar._0))) / polar._0;
    _164 = angleStuff(polar._4 + sead::Mathf::rad2deg(std::asin(sead::Mathf::clamp(ratio, -1.0f, 1.0f))));
    _164 = angleStuff(sead::Mathf::clamp(_164, _15c, _160));
}

// NON_MATCHING: input value lifetimes and scalar scheduling differ.
void CameraLockOnAimingAt::sub_7100774DEC(bool reset) {
    if (reset) {
        _188 = angleStuff(0);
        _18c = angleStuff(0);
    }
    sub_710077544C();
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    f32 longitude;
    if (stick.x == 0 && stick.y == 0 && *mGyro_s != 1 &&
        (*mGyro_s != 2 || sub_710092732C())) {
        _4c.sub_71008A4694(0);
        _188 = angleStuff(_188 + sead::Mathf::rad2deg(sub_7100923A38(_4c._0, _4c._24, 2, 0)));
        longitude = sub_7100923E2C();
    } else {
        _4c.sub_71008A4644();
        const f32 latitude_rate = sub_7100927238();
        ksys::VFRValue latitude_input(sub_7100927228() * latitude_rate * stick.y);
        latitude_input.updateStats();
        _188 = angleStuff(_188 + latitude_input.mean);
        const f32 longitude_rate = sub_71009272A8();
        ksys::VFRValue longitude_input(sub_7100927230() * longitude_rate * stick.x);
        longitude_input.updateStats();
        longitude = longitude_input.mean;
    }
    _18c = angleStuff(_18c + longitude);
    _188 = angleStuff(sead::Mathf::clamp(_188, _190, _194));
    const f32 latitude = angleStuff(_188 + _164);
    _188 = angleStuff(_188 - (latitude - sead::Mathf::clamp(latitude, _15c, _160)));
    _18c = angleStuff(sead::Mathf::clamp(_18c, _198, _19c));
}

// NON_MATCHING: radius and camera state scheduling differ.
void CameraLockOnAimingAt::sub_7100775000() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _178 = angleStuff(sead::Mathf::clamp(angleStuff(_188 + _164), _15c, _160));
    _180 = angleStuff(polar._4 - _178);
    _17c = angleStuff(_18c + _168);
    _184 = angleStuff(polar._8 - _17c);
    _1a0 = _16c;
    _1ac = camera->_860._0._c - _16c;
    _1b8 = polar._0 - sub_7100924D40(*mRadius_s);
    _1bc = camera->_860._0._24 - *mFovy_s;
    _1c0.sub_710079C384(10.0f, 0.0f);
    const act::Unk_7100922700 current(1.0f, polar._4, polar._8);
    const act::Unk_7100922700 target(1.0f, _178, _17c);
    sub_710074BDF8(current.sub_7100923254().dot(target.sub_7100923254()));
}

}  // namespace uking::action
