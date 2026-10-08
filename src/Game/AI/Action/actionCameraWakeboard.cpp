#include "Game/AI/Action/actionCameraWakeboard.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::action {

CameraWakeboard::CameraWakeboard(const InitArg& arg) : CameraAction(arg) {}

CameraWakeboard::~CameraWakeboard() = default;

// NON_MATCHING: target/curve stack lifetimes, clamp selection and scalar loads differ.
void CameraWakeboard::m33() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    _2c0.makeAllZero();
    _2c1 = 0;
    if (camera->_860._808.sub_710079ADC8(0x100) &&
        camera->_860._804.sub_710079AE50(0x100))
        _2c0.set(2);
    sub_7100787C08();
    f32 frame = 0.0f;
    ksys::Timer::update(&frame, 1.0f);
    if (frame <= 0.0f) {
        _114 = 0.01f;
        _118 = 100.0f;
    } else {
        _114 = frame;
        _118 = 1.0f / frame;
        if (!std::isfinite(_118)) {
            _114 = 0.01f;
            _118 = 100.0f;
        }
    }
    sub_7100787DB4();
    _ac = sead::Vector3f(0.0f, 0.0f, 0.0f);
    if (auto* current_camera = getCamera()) {
        _ac = current_camera->_860._444.getTranslation() +
              current_camera->_860._444.getBase(2) * *mOffsetZ_s;
        _ac.y += *mOffsetYBase_s;
    }
    _bc = 0.0f;
    camera->_860._7f8.reset(1);
    sead::Vector2f stick(0.0f, 0.0f);
    sub_7100924F08(&stick);
    if (stick.x != 0.0f || stick.y != 0.0f)
        camera->_860._7f8.set(1);
    if (camera->_860._7fc.sub_710079C0CC(0x800))
        camera->_860._7f8.set(1);
    if (stick.x != 0.0f || stick.y != 0.0f)
        _2c2 = 4;
    else if (sub_7100927110())
        _2c2 = 1;
    _2c2 = sub_7100926FD0() ? 4 : 0;
    _90 = 2.25f;
    if (auto* current_camera = getCamera()) {
        if (_2c2 == 1 && current_camera->_860._80f.sub_710079C1F4(1) &&
            current_camera->_860.sub_710079BF20())
            _90 = current_camera->_860._7e4;
    }
    _108 = 0.0f;
    _10c = 0.0f;
    sub_7100787FE8();
    const f32 vertical_speed = (player->getMtx().getTranslation().y -
                                sub_7100928868(camera->_860._164).y) * _118;
    f32 amount = sead::Mathf::clampMax(vertical_speed > 0.0f ? vertical_speed : -vertical_speed, 1.0f);
    amount = std::sin(amount * 3.1415927f - 1.5707964f);
    _d0 = _c4 = _298 + (amount + 1.0f) * 0.5f * (_29c - _298);
    const f32 acceleration = (vertical_speed - sub_7100928868(camera->_860._174).y) * _118;
    amount = sead::Mathf::clampMax(acceleration > 0.0f ? acceleration : -acceleration, 0.05f);
    _d4 = _c8 = (amount / 0.05f) * 0.79999995f + 0.1f;
    _f8 = 0.0f;
    if (camera->_860._7fc.sub_710079BFB0(0x100000)) {
        _70.sub_710079C510(1.0f);
        const act::Unk_7100922700 polar(_fc, _d8, _f0);
        camera->_860._0._c = _ac;
        camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
        f32 offset = *mOffsetYMin_s;
        if (*mOffsetYMin_s != *mOffsetYMax_s) {
            f32 value = polar._4;
            if (value < _258)
                value = _258;
            else if (!(value <= _25c))
                value = _25c;
            value = angleStuff(value);
            {
                act::Unk_71024741b8 curve;
                curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
                value = curve.sub_71009234D8(value, 10);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
                value = curve.eval(value);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(0.0f, _2a0, 1.0f - _2a4, 1.0f, *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
                value = curve.sub_71009234D8(value, 10);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(*mOffsetYMax_s, *mOffsetYMax_s, *mOffsetYMin_s, *mOffsetYMin_s,
                          *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
                offset = curve.eval(value);
            }
        }
        camera->_860._0._c.y += offset;
        camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    } else {
        _e8 = 0.0f;
        _ec = 0.0f;
    }
}

// NON_MATCHING: scalar and vector scheduling, curve lifetimes and clamps differ.
void CameraWakeboard::m34() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    const act::Unk_7100922700 current_polar = polar;
    sead::Vector2f stick = sead::Vector2f::zero;
    sub_7100924F08(&stick);
    const f32 stick_length = stick.length();
    const f32 stick_angle = std::atan2(stick.y, stick.x);
    const u8 previous_state = _2c2;
    if (!(stick_length <= 0.0f)) {
        _2c2 = 4;
    } else if (_2c2 == 2) {
        if (sub_7100927110())
            _2c2 = 1;
        else if (sub_7100926FD0())
            _2c2 = 4;
    } else if (_2c2 == 0) {
        if (_70._18 == 1.0f) {
            if (sub_7100927110())
                _2c2 = 1;
            else
                _2c2 = sub_7100926FD0() ? 4 : 2;
        }
    } else if (_2c2 == 1) {
        if (_70._18 == 1.0f)
            _2c2 = sub_7100926FD0() ? 4 : 2;
    } else {
        _2c2 = sub_7100927110() ? 1 : 3;
    }
    if (previous_state != _2c2)
        sub_7100787FE8();
    if (_2c2 == 4)
        camera->_860._7f8.set(1);
    else
        camera->_860._7f8.reset(1);
    _50.sub_710079C408();
    _70.sub_710079C408();
    const f32 progress = _70._18;
    f32 frame = 0.0f;
    ksys::Timer::update(&frame, 1.0f);
    if (frame <= 0.0f) {
        _114 = 0.01f;
        _118 = 100.0f;
    } else {
        _114 = frame;
        _118 = 1.0f / frame;
        if (!std::isfinite(_118)) {
            _114 = 0.01f;
            _118 = 100.0f;
        }
    }
    const f32 vertical_stick = stick_length * std::sin(stick_angle) * sub_7100927228();
    const f32 squared_stick = vertical_stick * vertical_stick *
                              (vertical_stick > 0.0f ? 1.0f : -1.0f);
    const bool fixed_latitude = _258 == _25c ||
                               (std::fabs(_258) == 180.0f && std::fabs(_25c) == 180.0f);
    f32 lat_ratio = 0.0f;
    f32 radius_ratio = 0.0f;
    if (!fixed_latitude) {
        f32 value = _d8;
        {
            act::Unk_71024741b8 curve;
            curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
            value = curve.sub_71009234D8(value, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
            lat_ratio = curve.eval(value);
        }
    }
    const f32 radius_min = _27c;
    const f32 radius_max = _280;
    if (radius_min != radius_max) {
        f32 value = _fc;
        {
            act::Unk_71024741b8 curve;
            curve.set(_27c, _27c, _280, _280, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
            value = curve.sub_71009234D8(value, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _284, 1.0f - _288, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
            radius_ratio = curve.eval(value);
        }
    }
    f32 latitude_delta = 0.0f;
    if (squared_stick == 0.0f) {
        if (!fixed_latitude && (lat_ratio < _e0 || _e4 < lat_ratio)) {
            const f32 limit = _e0 <= lat_ratio ? _e4 : _e0;
            latitude_delta = (limit - lat_ratio) * sub_7100791E44(sub_7100922090());
        }
    } else {
        latitude_delta = squared_stick * 0.006756757f * sub_7100927238() *
                         *mLatStickScale_s * _114;
    }
    const f32 remaining = 1.0f - progress;
    if (_2c2 == 2) {
        if (previous_state != 2) {
            _e8 = 0.0f;
            _ec = 0.0f;
        }
        f32 latitude = 0.0f;
        if (!player->m194() && !player->m188())
            latitude = sub_710092738C(camera->_860._0._c, camera->_860._0._0);
        _e8 += sub_7100791E44(0.05f) * (latitude - _e8);
        _ec += sub_7100791E44(0.1f) * (_e8 - _ec);
        polar._4 = angleStuff(_d8 + _ec) + angleStuff(remaining * _dc);
    } else {
        if (_2c2 != 3 && _2c2 != 1 && !fixed_latitude) {
            f32 value = lat_ratio + latitude_delta;
            {
                act::Unk_71024741b8 curve;
                curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
                value = curve.sub_71009234D8(value, 10);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
                _d8 = angleStuff(curve.eval(value));
            }
        }
        polar._4 = angleStuff(remaining * _dc) + _d8;
    }
    polar._4 = angleStuff(polar._4);
    if (_2c2 == 2 || _2c2 == 3) {
        sead::Vector3f forward = camera->_860._444.getBase(2);
        forward.y = 0.0f;
        f32 yaw = 0.0f;
        if (forward.x != 0.0f || forward.z != 0.0f)
            yaw = angleStuff(std::atan2(forward.x, forward.z) * 57.295776f + 180.0f);
        const f32 forward_length = forward.length();
        if (forward_length > 0.0f)
            forward *= 1.0f / forward_length;
        sead::Vector3f direction = polar.sub_7100923254();
        direction.y = 0.0f;
        const f32 direction_length = direction.length();
        if (direction_length > 0.0f)
            direction *= 1.0f / direction_length;
        f32 dot = forward.dot(direction);
        if (dot < -1.0f)
            dot = -1.0f;
        else if (!(dot <= 1.0f))
            dot = 1.0f;
        const f32 rate = sub_7100791E44(_274);
        f32 first;
        f32 second;
        if (dot <= 0.0f) {
            first = (dot + 1.0f) * 0.39999998f + 0.6f;
            second = (dot + 1.0f) * 0.0f + 1.0f;
        } else {
            first = (1.0f - dot) * 0.5f + 0.5f;
            second = (1.0f - dot) + 0.0f;
        }
        if (first < 0.0f)
            first = 0.0f;
        else if (!(first <= 1.0f))
            first = 1.0f;
        if (second < 0.0f)
            second = 0.0f;
        else if (!(second <= 1.0f))
            second = 1.0f;
        const sead::Vector3f player_pos = player->getMtx().getTranslation();
        const sead::Vector3f& old_pos = sub_7100928868(camera->_860._164);
        const f32 distance = sead::Vector3f(player_pos.x - old_pos.x, 0.0f,
                                           player_pos.z - old_pos.z).length();
        const f32 speed_ratio = sead::Mathf::clampMax(distance / _278, 1.0f);
        const f32 yaw_rate = rate * first * second * speed_ratio;
        _f8 = sead::Mathf::clampMax(_f8 + (yaw_rate - _f8) * 0.01f, yaw_rate);
        _f0 = angleStuff(angleStuff(angleStuff(yaw - _f0) * _f8) + _f0);
        polar._8 = angleStuff(angleStuff(remaining * _f4) + _f0);
    } else if (_2c2 == 4) {
        ksys::VFRValue rate(sub_7100927230() * stick_length * std::cos(stick_angle) *
                            sub_71009272A8() * *mLngStickScale_s);
        rate.updateStats();
        polar._8 = angleStuff(sub_7100924DFC(current_polar._8 + rate.mean));
        _f8 = 0.0f;
    } else {
        if (_2c2 == 1) {
            const sead::Vector3f forward = camera->_860._444.getBase(2);
            if (forward.x != 0.0f || forward.z != 0.0f) {
                const f32 yaw = angleStuff((std::atan2(forward.x, forward.z) + 3.1415927f) * 57.295776f);
                _f0 = angleStuff(angleStuff(angleStuff(yaw - _f0) *
                                            (progress * 0.39999998f + 0.6f)) + _f0);
            }
        }
        polar._8 = angleStuff(angleStuff(remaining * _f4) + _f0);
    }
    if (_2c2 == 2 || _2c2 == 3) {
        if (!fixed_latitude)
            sub_7100789098();
    } else if (_2c2 != 1 && radius_min != radius_max) {
        f32 value = radius_ratio + latitude_delta;
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _284, 1.0f - _288, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
            value = curve.sub_71009234D8(value, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(_27c, _27c, _280, _280, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
            _fc = curve.eval(value);
        }
    }
    polar._0 = sub_7100924D40(_fc + remaining * _100);
    if (!camera->_860._80e.sub_710079C1C8(4))
        ksys::VFR::lerp(&_c0, _290, sub_7100922384());
    else
        _c0 = _294;
    _cc = _c0;
    const f32 vertical_speed = (player->getMtx().getTranslation().y -
                               sub_7100928868(camera->_860._164).y) * _118;
    const f32 acceleration = (vertical_speed - sub_7100928868(camera->_860._174).y) * _118;
    f32 amount = sead::Mathf::clampMax(vertical_speed > 0.0f ? vertical_speed : -vertical_speed, 1.0f);
    amount = std::sin(amount * 3.1415927f - 1.5707964f);
    const f32 vertical_rate = _298 + (amount + 1.0f) * 0.5f * (_29c - _298);
    amount = sead::Mathf::clampMax(acceleration > 0.0f ? acceleration : -acceleration, 0.05f);
    const f32 acceleration_rate = (amount / 0.05f) * 0.79999995f + 0.1f;
    const f32 rate = sub_7100791E44(0.1f);
    _c8 += rate * (acceleration_rate - _c8);
    if (player->getRootAi() &&
        (player->getRootAi()->isCurrentAction("よじ登り飛びつき") ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("小段差よじ登り壁つかみ")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("ぶら下がりからのよじ登り")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("段差登り"))))
        _c4 = 0.08f;
    else
        _c4 += sub_7100791E44(_c8) * (vertical_rate - _c4);
    _d4 += rate * (acceleration_rate - _d4);
    if (player->getRootAi() &&
        (player->getRootAi()->isCurrentAction("よじ登り飛びつき") ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("小段差よじ登り壁つかみ")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("ぶら下がりからのよじ登り")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("段差登り"))))
        _d0 = 0.08f;
    else
        _d0 += sub_7100791E44(_d4) * (vertical_rate - _d0);
    sub_71007893F4();
    f32 side = 0.0f;
    if (auto* camera_actor = getCameraActor()) {
        side = camera_actor->_860.sub_710079BE40() * 28.571428f;
        if (side < -1.0f)
            side = -1.0f;
        else if (!(side <= 1.0f))
            side = 1.0f;
    }
    _bc += sub_7100791E44(_2a8) * (-(side * *mSideOffset_s) - _bc);
    sead::Vector3f target = sead::Vector3f::zero;
    sub_71007894D4(&target, &polar);
    const f32 rate_xz = sub_7100791E44(_c0);
    const f32 rate_y = sub_7100791E44(_c4);
    _94.x += rate_xz * (target.x - _94.x);
    _94.y += rate_y * (target.y - _94.y);
    _94.z += rate_xz * (target.z - _94.z);
    camera->_860._0._c = _94 + _a0 * remaining;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    if (!camera->_860._80e.sub_710079C1C8(4))
        _108 += sub_7100791E44(_2bc) * (0.0f - _108);
    else
        _108 = _104;
    _10c += sub_7100791E44(_2b8) * (_108 - _10c);
    camera->_860._0._24 = sub_7100924D50(_2b0 + _10c + remaining * _110);
    _2c1 = _2c0.getDirect();
    camera->sub_71007953C8();
}

void CameraWakeboard::m36() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatLimitMin_s, "LatLimitMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatLimitMax_s, "LatLimitMax");
    getStaticParam(&mLatMinWidth_s, "LatMinWidth");
    getStaticParam(&mLatMaxWidth_s, "LatMaxWidth");
    getStaticParam(&mLatMinWeight_s, "LatMinWeight");
    getStaticParam(&mLatMaxWeight_s, "LatMaxWeight");
    getStaticParam(&mLat_s, "Lat");
    getStaticParam(&mLngCus_s, "LngCus");
    getStaticParam(&mLngCusSpeedEffect_s, "LngCusSpeedEffect");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mRadiusMin_s, "RadiusMin");
    getStaticParam(&mRadiusMax_s, "RadiusMax");
    getStaticParam(&mRadiusMinWidth_s, "RadiusMinWidth");
    getStaticParam(&mRadiusMaxWidth_s, "RadiusMaxWidth");
    getStaticParam(&mRadiusMinWeight_s, "RadiusMinWeight");
    getStaticParam(&mRadiusMaxWeight_s, "RadiusMaxWeight");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mOffsetYBase_s, "OffsetYBase");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mOffsetYMinWidth_s, "OffsetYMinWidth");
    getStaticParam(&mOffsetYMaxWidth_s, "OffsetYMaxWidth");
    getStaticParam(&mOffsetYMinWeight_s, "OffsetYMinWeight");
    getStaticParam(&mOffsetYMaxWeight_s, "OffsetYMaxWeight");
    getStaticParam(&mOffsetZ_s, "OffsetZ");
    getStaticParam(&mSideOffset_s, "SideOffset");
    getStaticParam(&mSideOffsetCus_s, "SideOffsetCus");
    getStaticParam(&mAtHCusNormal_s, "AtHCusNormal");
    getStaticParam(&mAtHCusSpurt_s, "AtHCusSpurt");
    getStaticParam(&mAtVCusMin_s, "AtVCusMin");
    getStaticParam(&mAtVCusMax_s, "AtVCusMax");
    getStaticParam(&mFovyNormal_s, "FovyNormal");
    getStaticParam(&mFovySpurt_s, "FovySpurt");
    getStaticParam(&mFovyCusAccel_s, "FovyCusAccel");
    getStaticParam(&mFovyCusDecel_s, "FovyCusDecel");
    getStaticParam(&mAutoModeConnect_s, "AutoModeConnect");
}

void CameraWakeboard::sub_71007893F4() {
    sead::Vector3f target = sead::Vector3f::zero;
    if (auto* camera = getCamera()) {
        const sead::Matrix34f& mtx = camera->_860._444;
        target = mtx.getTranslation();
        target.y += *mOffsetYBase_s;
        target += mtx.getBase(2) * *mOffsetZ_s;
    }
    const f32 rate_xz = sub_7100791E44(_cc);
    const f32 rate_y = sub_7100791E44(_d0);
    _ac.x += rate_xz * (target.x - _ac.x);
    _ac.y += rate_y * (target.y - _ac.y);
    _ac.z += rate_xz * (target.z - _ac.z);
}

// NON_MATCHING: stack slots, saved float registers and output stores differ.
void CameraWakeboard::sub_71007894D4(sead::Vector3f* out, const act::Unk_7100922700* polar) {
    *out = _ac;
    f32 height = 0.0f;
    if (sub_71009269F8(*out, &height)) {
        height += 0.4f;
        out->y = sead::Mathf::max(out->y, height);
    }
    f32 offset = 0.0f;
    sub_710078A818(polar->_4, &offset);
    out->y += offset;
    if (auto* camera = getCameraActor()) {
        const sead::Vector3f base = camera->_860._444.getBase(0);
        sead::Vector3f direction(-base.x, 0.0f, -base.z);
        const f32 length = sead::Vector3f(base.x, 0.0f, base.z).length();
        if (length > 0.0f)
            direction *= _bc / length;
        *out += direction;
    }
}

// NON_MATCHING: curve lifetimes reuse one stack slot and the equality branch differs.
void CameraWakeboard::sub_710078A818(f32 latitude, f32* out) {
    if (*mOffsetYMin_s == *mOffsetYMax_s) {
        *out = *mOffsetYMin_s;
        return;
    }
    f32 value = angleStuff(latitude);
    if (value < _258)
        value = _258;
    else if (!(value <= _25c))
        value = _25c;
    value = angleStuff(value);
    {
        act::Unk_71024741b8 curve;
        curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.eval(value);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _2a0, 1.0f - _2a4, 1.0f, *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(*mOffsetYMax_s, *mOffsetYMax_s, *mOffsetYMin_s, *mOffsetYMin_s,
                  *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
        *out = curve.eval(value);
    }
}

// NON_MATCHING: vector store pairing and saved float registers differ.
void CameraWakeboard::sub_710078A0C0() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    _d8 = _270;
    _dc = angleStuff(polar._4 - _270);
    const sead::Vector3f forward = camera->_860._444.getBase(2);
    if (forward.x == 0.0f && forward.z == 0.0f) {
        _f0 = polar._8;
        _f4 = angleStuff(0.0f);
    } else {
        const f32 longitude = sead::Mathf::rad2deg(std::atan2(forward.x, forward.z) + sead::Mathf::pi());
        _f0 = angleStuff(longitude);
        _f4 = angleStuff(polar._8 - angleStuff(longitude));
    }
    sead::Vector3f target = sead::Vector3f::zero;
    sub_71007894D4(&target, &polar);
    _94 = target;
    _a0 = camera->_860._0._c - target;
    _fc = _28c;
    _100 = polar._0 - _28c;
    if (auto* current = getCamera())
        _110 = (current->_860._0._24 - _10c) - _2b0;
    if (!_2c0.isOn(1))
        _50.sub_710079C384(10.0f, 0.0f);
    _70.sub_710079C384(10.0f, 0.0f);
}

// NON_MATCHING: target-vector copies and float registers differ.
void CameraWakeboard::sub_710078A294() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 duration = 0.0f;
    if (angleStuff(_dc) != angleStuff(0.0f))
        duration = std::fmax((_dc > 0.0f ? _dc : -_dc) * 0.5f, 0.0f);
    const sead::Vector3f forward = camera->_860._444.getBase(2);
    if (forward.x == 0.0f && forward.z == 0.0f) {
        _f0 = polar._8;
        _f4 = angleStuff(0.0f);
    } else {
        const f32 longitude = sead::Mathf::rad2deg(std::atan2(forward.x, forward.z) + sead::Mathf::pi());
        _f0 = angleStuff(longitude);
        _f4 = angleStuff(polar._8 - angleStuff(longitude));
    }
    if (angleStuff(_f4) != angleStuff(0.0f))
        duration = sead::Mathf::max(duration, (_f4 > 0.0f ? _f4 : -_f4) * 0.25f);
    if (_100 != 0.0f)
        duration = sead::Mathf::clampMin(duration, (_100 > 0.0f ? _100 : -_100) * 2.5f);
    sead::Vector3f target = sead::Vector3f::zero;
    sub_71007894D4(&target, &polar);
    _94 = target;
    _a0 = camera->_860._0._c - target;
    if (_a0 != sead::Vector3f(0.0f, 0.0f, 0.0f)) {
        const f32 length = _a0.length();
        if (length > 5.0f)
            duration = sead::Mathf::clampMin(duration, (length > 0.0f ? length : -length) * 2.5f);
    }
    if (auto* current = getCamera())
        _110 = (current->_860._0._24 - _10c) - _2b0;
    const f32 degrees = sead::Mathf::rad2deg(_110);
    duration = sead::Mathf::clampMin(duration, (degrees > 0.0f ? degrees : -degrees) * 0.5f);
    if (duration > 0.0f)
        duration = sead::Mathf::clamp(duration, 15.0f, 90.0f);
    if (!_2c0.isOn(1))
        _50.sub_710079C384(duration, 0.0f);
    _70.sub_710079C384(duration, 0.0f);
    _70.sub_710079C3F8(_2ac);
    sub_710074BCB4();
}

void CameraWakeboard::sub_7100789A74() {
    sub_710078A0C0();
    _70.sub_710079C3F8(1.0f);
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 current(camera->_860._0._0 - camera->_860._0._c);
        const act::Unk_7100922700 a(1.0f, current._4, current._8);
        const act::Unk_7100922700 b(1.0f, _d8, _f0);
        sub_710074BDF8(a.sub_7100923254().dot(b.sub_7100923254()));
    }
}

// NON_MATCHING: bound values are reloaded after wrapping calls.
void CameraWakeboard::sub_7100789B5C() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 difference = 0.0f;
    if (angleStuff(polar._4) < angleStuff(_258)) {
        _d8 = _258;
        difference = polar._4 - _d8;
    } else if (angleStuff(_25c) < angleStuff(polar._4)) {
        _d8 = _25c;
        difference = polar._4 - _d8;
    } else {
        _d8 = polar._4;
    }
    _dc = angleStuff(difference);
    _fc = polar._0;
    _100 = 0.0f;
    sub_710078A294();
}

// NON_MATCHING: width clamp branches and saved float registers differ.
void CameraWakeboard::sub_7100787C08() {
    sub_710078A5C0();
    _274 = sub_7100924D80(*mLngCus_s);
    _278 = sead::Mathf::clampMin(*mLngCusSpeedEffect_s, 0.01f);
    _27c = sub_7100924D40(*mRadiusMin_s);
    _280 = sub_7100924D40(*mRadiusMax_s);
    _284 = sead::Mathf::clamp(*mRadiusMinWidth_s, 0.0f, 0.5f);
    _288 = sead::Mathf::clamp(*mRadiusMaxWidth_s, 0.0f, 0.5f);
    _28c = sub_7100924D40(*mRadius_s);
    _290 = sub_7100924D80(*mAtHCusNormal_s);
    _294 = sub_7100924D80(*mAtHCusSpurt_s);
    sub_7100924DA4(*mAtVCusMin_s, *mAtVCusMax_s, &_298, &_29c);
    _2a0 = sead::Mathf::clamp(*mOffsetYMinWidth_s, 0.0f, 0.5f);
    _2a4 = sead::Mathf::clamp(*mOffsetYMaxWidth_s, 0.0f, 0.5f);
    _2b0 = sub_7100924D50(*mFovyNormal_s);
    _2b4 = sub_7100924D50(*mFovySpurt_s);
    _2b8 = sub_7100924D80(*mFovyCusAccel_s);
    _2bc = sub_7100924D80(*mFovyCusDecel_s);
    _2a8 = sub_7100924D80(*mSideOffsetCus_s);
    _2ac = sead::Mathf::clampMin(*mAutoModeConnect_s, 0.0f);
    _104 = _2b4 - _2b0;
}

// NON_MATCHING: saved camera-state copies have different scheduling.
void CameraWakeboard::sub_7100787DB4() {
    auto* camera = getCamera();
    if (!camera || !camera->_860.sub_710079C184(0x100))
        return;
    if ((camera->_860._0._c - camera->_860._0._0).squaredLength() < 400.0f)
        return;
    camera->_860._a8 = camera->_860._e0;
    camera->_860._70 = camera->_860._e0;
    camera->_860._38 = camera->_860._e0;
    camera->_860._0 = camera->_860._e0;
    act::Unk_7100922700 polar(camera->_860._0._c - camera->_860._0._0);
    polar._0 = _28c;
    camera->_860._0._c = camera->_860._0._0 + polar.sub_7100923254();
}

// NON_MATCHING: width clamp branches, curve storage and parameter loads differ.
void CameraWakeboard::sub_710078A5C0() {
    _268 = sead::Mathf::clamp(*mLatMinWidth_s, 0.0f, 0.5f);
    _26c = sead::Mathf::clamp(*mLatMaxWidth_s, 0.0f, 0.5f);
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_258, &_25c);
    sub_7100924CDC(*mLatLimitMin_s, *mLatLimitMax_s, &_260, &_264);
    _260 = angleStuff(sead::Mathf::clampMin(_260, _258));
    _264 = angleStuff(sead::Mathf::clampMax(_264, _25c));
    if (angleStuff(_258) == angleStuff(_25c)) {
        _e0 = 0.0f;
        _e4 = 0.0f;
    } else {
        f32 value;
        {
            act::Unk_71024741b8 curve;
            curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
            value = curve.sub_71009234D8(_260, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
            _e0 = curve.eval(value);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
            value = curve.sub_71009234D8(_264, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
            _e4 = curve.eval(value);
        }
    }
    _270 = angleStuff(sead::Mathf::clamp(angleStuff(*mLat_s), _258, _25c));
}

// NON_MATCHING: prepared-field loads and saved float registers differ.
void CameraWakeboard::sub_7100787FE8() {
    switch (_2c2) {
    case 0:
        sub_710078A0C0();
        _70.sub_710079C3F8(_90);
        break;
    case 1:
        sub_7100789A74();
        break;
    case 2:
        if (auto* camera = getCamera()) {
            const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
            _d8 = _270;
            _dc = angleStuff(polar._4 - _270);
            _fc = _28c;
            _100 = polar._0 - _28c;
            sub_710078A294();
        }
        break;
    case 3:
        sub_7100789B5C();
        break;
    default:
        sub_7100789C50();
        break;
    }
    _90 = 1.0f;
    _2c0.set(1);
}

// NON_MATCHING: curve lifetimes, clamp branches and saved float registers differ.
void CameraWakeboard::sub_7100789098() {
    if (_258 == _25c || (std::fabs(_258) == 180.0f && std::fabs(_25c) == 180.0f) ||
        _27c == _280) {
        _fc = _28c;
        return;
    }
    f32 value = _270;
    {
        act::Unk_71024741b8 curve;
        curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    f32 base_lat_ratio;
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        base_lat_ratio = curve.eval(value);
    }
    value = angleStuff(_ec + _d8);
    if (value < _258)
        value = _258;
    else if (!(value <= _25c))
        value = _25c;
    value = angleStuff(value);
    {
        act::Unk_71024741b8 curve;
        curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    f32 lat_ratio;
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        lat_ratio = curve.eval(value);
    }
    const f32 edge = lat_ratio > base_lat_ratio ? 1.0f : -1.0f;
    f32 blend = 1.0f;
    if (edge - base_lat_ratio != 0.0f)
        blend = (lat_ratio - base_lat_ratio) / (edge - base_lat_ratio);
    f32 min = 1.0f;
    f32 max = 1.0f;
    sub_7100924C94(_27c, _280, &min, &max);
    value = _28c;
    if (value < min)
        value = min;
    else if (!(value <= max))
        value = max;
    {
        act::Unk_71024741b8 curve;
        curve.set(_27c, _27c, _280, _280, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _284, 1.0f - _288, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.eval(value);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _284, 1.0f - _288, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.sub_71009234D8(value + blend * (edge - value), 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(_27c, _27c, _280, _280, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.eval(value);
    }
    const f32 radius = sub_7100924D40(value);
    const f32 rate = sub_7100791E44(0.6f);
    _fc += rate * (radius - _fc);
}

// NON_MATCHING: curve lifetimes, clamp selection and vector-copy scheduling differ.
void CameraWakeboard::sub_7100789C50() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 difference = 0.0f;
    if (angleStuff(polar._4) < angleStuff(_258)) {
        _d8 = _258;
        difference = polar._4 - _d8;
    } else if (angleStuff(_25c) < angleStuff(polar._4)) {
        _d8 = _25c;
        difference = polar._4 - _d8;
    } else {
        _d8 = polar._4;
    }
    _dc = angleStuff(difference);
    f32 duration = 0.0f;
    if (angleStuff(_dc) != angleStuff(0.0f))
        duration = sead::Mathf::clampMin((_dc > 0.0f ? _dc : -_dc) * 0.75f, 10.0f);
    _f0 = polar._8;
    _f4 = angleStuff(0.0f);
    f32 value = _d8;
    {
        act::Unk_71024741b8 curve;
        curve.set(_258, _258, _25c, _25c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.eval(value);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _284, 1.0f - _288, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(_27c, _27c, _280, _280, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.eval(value);
    }
    const f32 radius_difference = polar._0 - value;
    if (!((radius_difference > 0.0f ? radius_difference : -radius_difference) > 1.4f)) {
        f32 min = 0.0f;
        f32 max = 0.0f;
        sub_7100924C94(_27c, _280, &min, &max);
        value = polar._0;
        if (value < min)
            value = min;
        else if (!(value <= max))
            value = max;
    }
    _fc = value;
    _100 = polar._0 - value;
    if (_100 != 0.0f)
        duration = sead::Mathf::clampMin(std::fmax(duration, 10.0f),
                                       (_100 > 0.0f ? _100 : -_100) * 0.5f);
    sead::Vector3f target = sead::Vector3f::zero;
    sub_71007894D4(&target, &polar);
    _94 = target;
    _a0 = camera->_860._0._c - target;
    if (_a0 != sead::Vector3f(0.0f, 0.0f, 0.0f)) {
        const f32 length = _a0.length();
        duration = sead::Mathf::clampMin(duration, 10.0f);
        if (!(length <= 5.0f))
            duration = sead::Mathf::clampMin(duration, (length > 0.0f ? length : -length) * 2.5f);
    }
    if (auto* current_camera = getCamera())
        _110 = (current_camera->_860._0._24 - _10c) - _2b0;
    const f32 degrees = _110 * 57.295776f;
    duration = sead::Mathf::clampMin(duration, (degrees > 0.0f ? degrees : -degrees) * 0.5f);
    duration = sead::Mathf::clampMax(duration, 90.0f);
    if (!_2c0.isOn(1))
        _50.sub_710079C384(duration, 0.0f);
    _70.sub_710079C384(duration, 0.0f);
    _70.sub_710079C3F8(1.0f);
    sub_710074BCB4();
}

}  // namespace uking::action
