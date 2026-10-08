#include "Game/AI/Action/actionCameraShieldSurfing.h"
#include "KingSystem/Utils/MathUtil.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::action {

CameraShieldSurfing::CameraShieldSurfing(const InitArg& arg) : CameraAction(arg) {}

CameraShieldSurfing::~CameraShieldSurfing() = default;

// NON_MATCHING: target and curve lifetimes, scalar loads and float scheduling differ.
void CameraShieldSurfing::m33() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    _284.makeAllZero();
    _285 = 0;
    if (camera->_860._808.sub_710079ADC8(0x100) &&
        camera->_860._804.sub_710079AE50(0x100))
        _284.set(2);
    sub_710077EBEC();
    f32 frame = 0.0f;
    ksys::Timer::update(&frame, 1.0f);
    if (frame <= 0.0f) {
        _10c = 0.01f;
        _110 = 100.0f;
    } else {
        _10c = frame;
        _110 = 1.0f / frame;
        if (!std::isfinite(_110)) {
            _10c = 0.01f;
            _110 = 100.0f;
        }
    }
    sub_710077ED58();
    _ac = sead::Vector3f(0.0f, 0.0f, 0.0f);
    if (auto* current_camera = getCamera())
        _ac = current_camera->_860._2b8;
    _bc = 0.0f;
    _c0 = 0.0f;
    camera->_860._7f8.reset(1);
    sead::Vector2f stick(0.0f, 0.0f);
    sub_7100924F08(&stick);
    if (stick.x != 0.0f || stick.y != 0.0f)
        camera->_860._7f8.set(1);
    if (camera->_860._7fc.sub_710079C0CC(0x800))
        camera->_860._7f8.set(1);
    if (stick.x != 0.0f || stick.y != 0.0f)
        _286 = 5;
    else if (sub_7100927110())
        _286 = 2;
    _286 = sub_7100926FD0() ? 5 : (camera->_860._7fa.getDirect() & 1);
    _90 = 2.25f;
    if (auto* current_camera = getCamera()) {
        if (_286 == 2 && current_camera->_860._80f.sub_710079C1F4(1) &&
            current_camera->_860.sub_710079BF20())
            _90 = current_camera->_860._7e4;
    }
    sub_710077EF8C();
    const f32 vertical_speed = (player->getMtx().getTranslation().y -
                                sub_7100928868(camera->_860._164).y) * _110;
    f32 amount = sead::Mathf::clampMax(vertical_speed > 0.0f ? vertical_speed : -vertical_speed, 1.0f);
    amount = std::sin(amount * 3.1415927f - 1.5707964f);
    _d4 = _c8 = _260 + (amount + 1.0f) * 0.5f * (_264 - _260);
    const f32 acceleration = (vertical_speed - sub_7100928868(camera->_860._174).y) * _110;
    amount = sead::Mathf::clampMax(acceleration > 0.0f ? acceleration : -acceleration, 0.05f);
    _d8 = _cc = (amount / 0.05f) * 0.79999995f + 0.1f;
    _fc = 0.0f;
    if (!camera->_860._7fc.sub_710079BFB0(0x100000)) {
        _70.sub_710079C510(1.0f);
        const act::Unk_7100922700 polar(_100, _dc, _f4);
        camera->_860._0._c = _ac;
        camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
        f32 offset = *mOffsetYMin_s;
        if (*mOffsetYMin_s != *mOffsetYMax_s) {
            f32 value = polar._4;
            if (value < _228)
                value = _228;
            else if (!(value <= _22c))
                value = _22c;
            value = angleStuff(value);
            {
                act::Unk_71024741b8 curve;
                curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
                value = curve.sub_71009234D8(value, 10);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
                value = curve.eval(value);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
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
        _ec = 0.0f;
        _f0 = 0.0f;
    }
}

// NON_MATCHING: state and scalar scheduling, vector copies and curve lifetimes differ.
void CameraShieldSurfing::m34() {
    auto* camera = getCamera();
    if (!camera)
        return;
    auto* player = sub_7100926A14();
    if (!player)
        return;
    act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    const act::Unk_7100922700 current_polar = polar;
    sead::Vector2f stick(0.0f, 0.0f);
    sub_7100924F08(&stick);
    const f32 stick_length = stick.length();
    const f32 stick_angle = std::atan2(stick.y, stick.x);
    const u8 previous_state = _286;
    if (!(stick_length <= 0.0f)) {
        _286 = 5;
    } else if (_286 < 2) {
        if (_70._18 == 1.0f) {
            if (sub_7100927110())
                _286 = 2;
            else
                _286 = sub_7100926FD0() ? 5 : 4;
        }
    } else if (_286 == 2) {
        if (_70._18 == 1.0f)
            _286 = sub_7100926FD0() ? 5 : 3;
    } else if (_286 == 3) {
        if (sub_7100927110())
            _286 = 2;
        else if (sub_7100926FD0())
            _286 = 5;
    } else {
        _286 = sub_7100927110() ? 2 : 4;
    }
    if (previous_state != _286)
        sub_710077EF8C();
    if (_286 == 4 || _286 == 5)
        camera->_860._7f8.set(1);
    else
        camera->_860._7f8.reset(1);
    _50.sub_710079C408();
    _70.sub_710079C408();
    const f32 progress = _70._18;
    f32 frame = 0.0f;
    ksys::Timer::update(&frame, 1.0f);
    if (frame <= 0.0f) {
        _10c = 0.01f;
        _110 = 100.0f;
    } else {
        _10c = frame;
        _110 = 1.0f / frame;
        if (!std::isfinite(_110)) {
            _10c = 0.01f;
            _110 = 100.0f;
        }
    }
    const f32 vertical_stick = stick_length * std::sin(stick_angle) * sub_7100927228();
    const f32 squared_stick = vertical_stick * vertical_stick *
                              (vertical_stick > 0.0f ? 1.0f : -1.0f);
    const bool fixed_latitude = _228 == _22c ||
                               (std::fabs(_228) == 180.0f && std::fabs(_22c) == 180.0f);
    f32 lat_ratio = 0.0f;
    f32 radius_ratio = 0.0f;
    if (!fixed_latitude) {
        f32 value = _dc;
        {
            act::Unk_71024741b8 curve;
            curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
            value = curve.sub_71009234D8(value, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
            lat_ratio = curve.eval(value);
        }
    }
    const f32 radius_min = _24c;
    const f32 radius_max = _250;
    if (radius_min != radius_max) {
        f32 value = _100;
        {
            act::Unk_71024741b8 curve;
            curve.set(_24c, _24c, _250, _250, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
            value = curve.sub_71009234D8(value, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _254, 1.0f - _258, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
            radius_ratio = curve.eval(value);
        }
    }
    f32 latitude_delta = 0.0f;
    if (squared_stick == 0.0f) {
        if (!fixed_latitude && (lat_ratio < _e4 || _e8 < lat_ratio)) {
            const f32 limit = _e4 <= lat_ratio ? _e8 : _e4;
            latitude_delta = (limit - lat_ratio) * sub_7100791E44(sub_7100922090());
        }
    } else {
        latitude_delta = squared_stick * 0.006756757f * sub_7100927238() *
                         *mLatStickScale_s * _10c;
    }
    const f32 remaining = 1.0f - progress;
    if (_286 == 3) {
        if (previous_state != 3) {
            _ec = 0.0f;
            _f0 = 0.0f;
        }
        f32 latitude = 0.0f;
        if (!player->m194() && !player->m188())
            latitude = sub_710092738C(camera->_860._0._c, camera->_860._0._0);
        _ec += sub_7100791E44(0.05f) * (latitude - _ec);
        _f0 += sub_7100791E44(0.1f) * (_ec - _f0);
        polar._4 = angleStuff(_dc + _f0) + angleStuff(remaining * _e0);
    } else if (_286 == 4) {
        // The original computes this transition angle but clamps the previous polar latitude.
        angleStuff(angleStuff(remaining * _e0) + _dc);
    } else {
        if (_286 > 4 && !fixed_latitude) {
            f32 value = lat_ratio + latitude_delta;
            {
                act::Unk_71024741b8 curve;
                curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
                value = curve.sub_71009234D8(value, 10);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
                _dc = angleStuff(curve.eval(value));
            }
        }
        polar._4 = angleStuff(remaining * _e0) + _dc;
    }
    if (_286 != 4)
        polar._4 = angleStuff(polar._4);
    polar._4 = angleStuff(sub_7100924CAC(polar._4));
    if (_286 == 3 || _286 == 4) {
        sead::Vector3f forward = camera->_860._270.getBase(2);
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
        const f32 rate = sub_7100791E44(_244);
        f32 first;
        f32 second;
        if (dot <= 0.0f) {
            first = sead::lerp(0.6f, 1.0f, dot + 1.0f);
            second = sead::lerp(1.0f, 1.0f, dot + 1.0f);
        } else {
            first = sead::lerp(0.5f, 1.0f, 1.0f - dot);
            second = sead::lerp(0.0f, 1.0f, 1.0f - dot);
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
        const f32 speed_ratio = sead::Mathf::clampMax(distance / _248, 1.0f);
        const f32 yaw_rate = rate * first * second * speed_ratio;
        _fc = sead::Mathf::clampMax(_fc + (yaw_rate - _fc) * 0.01f, yaw_rate);
        _f4 = angleStuff(angleStuff(angleStuff(yaw - _f4) * _fc) + _f4);
        polar._8 = angleStuff(angleStuff(remaining * _f8) + _f4);
    } else if (_286 == 5) {
        ksys::VFRValue rate(sub_7100927230() * stick_length * std::cos(stick_angle) *
                            sub_71009272A8() * *mLngStickScale_s);
        rate.updateStats();
        polar._8 = angleStuff(sub_7100924DFC(current_polar._8 + rate.mean));
        _fc = 0.0f;
    } else {
        if (_286 == 2) {
            const sead::Vector3f forward = camera->_860._270.getBase(2);
            if (forward.x != 0.0f || forward.z != 0.0f) {
                const f32 yaw = angleStuff((std::atan2(forward.x, forward.z) + 3.1415927f) * 57.295776f);
                _f4 = angleStuff(angleStuff(angleStuff(yaw - _f4) *
                                            (progress * 0.39999998f + 0.6f)) + _f4);
            }
        }
        polar._8 = angleStuff(angleStuff(remaining * _f8) + _f4);
    }
    if (_286 > 2) {
        if (_286 == 3 || _286 == 4) {
            if (!fixed_latitude)
                sub_710077FFA0();
        } else if (radius_min != radius_max) {
            f32 value = radius_ratio + latitude_delta;
            {
                act::Unk_71024741b8 curve;
                curve.set(0.0f, _254, 1.0f - _258, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
                value = curve.sub_71009234D8(value, 10);
            }
            {
                act::Unk_71024741b8 curve;
                curve.set(_24c, _24c, _250, _250, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
                _100 = curve.eval(value);
            }
        }
    }
    polar._0 = sub_7100924D40(_100 + remaining * _104);
    _c4 = _d0 = _278;
    const f32 vertical_speed = (player->getMtx().getTranslation().y -
                               sub_7100928868(camera->_860._164).y) * _110;
    const f32 acceleration = (vertical_speed - sub_7100928868(camera->_860._174).y) * _110;
    f32 amount = sead::Mathf::clampMax(vertical_speed > 0.0f ? vertical_speed : -vertical_speed, 1.0f);
    amount = std::sin(amount * 3.1415927f - 1.5707964f);
    const f32 vertical_rate = _260 + (amount + 1.0f) * 0.5f * (_264 - _260);
    amount = sead::Mathf::clampMax(acceleration > 0.0f ? acceleration : -acceleration, 0.05f);
    const f32 acceleration_rate = (amount / 0.05f) * 0.79999995f + 0.1f;
    const f32 rate = sub_7100791E44(0.1f);
    _cc += rate * (acceleration_rate - _cc);
    if (player->getRootAi() &&
        (player->getRootAi()->isCurrentAction("よじ登り飛びつき") ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("小段差よじ登り壁つかみ")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("ぶら下がりからのよじ登り")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("段差登り"))))
        _c8 = 0.08f;
    else
        _c8 += sub_7100791E44(_cc) * (vertical_rate - _c8);
    _d8 += rate * (acceleration_rate - _d8);
    if (player->getRootAi() &&
        (player->getRootAi()->isCurrentAction("よじ登り飛びつき") ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("小段差よじ登り壁つかみ")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("ぶら下がりからのよじ登り")) ||
         (player->getRootAi() && player->getRootAi()->isCurrentAction("段差登り"))))
        _d4 = 0.08f;
    else
        _d4 += sub_7100791E44(_d8) * (vertical_rate - _d4);
    sead::Vector3f base_target(0.0f, 0.0f, 0.0f);
    if (auto* current_camera = getCamera())
        base_target = current_camera->_860._2b8;
    const f32 base_rate_xz = sub_7100791E44(_d0);
    const f32 base_rate_y = sub_7100791E44(_d4);
    _ac.x += base_rate_xz * (base_target.x - _ac.x);
    _ac.y += base_rate_y * (base_target.y - _ac.y);
    _ac.z += base_rate_xz * (base_target.z - _ac.z);
    sub_71007802FC();
    sead::Vector3f target(0.0f, 0.0f, 0.0f);
    sub_71007803E0(&target, &polar);
    const f32 rate_xz = sub_7100791E44(_c4);
    const f32 rate_y = sub_7100791E44(_c8);
    _94.x += rate_xz * (target.x - _94.x);
    _94.y += rate_y * (target.y - _94.y);
    _94.z += rate_xz * (target.z - _94.z);
    camera->_860._0._c = _94 + _a0 * remaining;
    camera->_860._0._0 = camera->_860._0._c + polar.sub_7100923254();
    camera->_860._0._24 = sub_7100924D50(_27c + remaining * _108);
    _285 = _284.getDirect();
    camera->sub_71007953C8();
}

void CameraShieldSurfing::m36() {
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
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mOffsetYMinWidth_s, "OffsetYMinWidth");
    getStaticParam(&mOffsetYMaxWidth_s, "OffsetYMaxWidth");
    getStaticParam(&mOffsetYMinWeight_s, "OffsetYMinWeight");
    getStaticParam(&mOffsetYMaxWeight_s, "OffsetYMaxWeight");
    getStaticParam(&mSideOffset_s, "SideOffset");
    getStaticParam(&mSideOffsetCus_s, "SideOffsetCus");
    getStaticParam(&mSideOffsetRateCus_s, "SideOffsetRateCus");
    getStaticParam(&mAtHCus_s, "AtHCus");
    getStaticParam(&mAtVCusMin_s, "AtVCusMin");
    getStaticParam(&mAtVCusMax_s, "AtVCusMax");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mAutoModeConnect_s, "AutoModeConnect");
}

// NON_MATCHING: the original branches on stick.x > 0 and selects the other two values with one fcsel (ours: two fcsel and no
// branch), and computes SideOffset * _c0 before the call of sub_7100791E44(_270) (ours after).
void CameraShieldSurfing::sub_71007802FC() {
    ksys::act::acc::PlayerBase player;
    sub_7100926A50(&player);
    if (player.hasProc() && player.isBgCrossFoot()) {
        sead::Vector2f stick = sead::Vector2f::zero;
        sub_7100927054(&stick);
        f32 sign;
        if (stick.x > 0.0f)
            sign = 1.0f;
        else if (stick.x < 0.0f)
            sign = -1.0f;
        else
            sign = 0.0f;
        _c0 += sub_7100791E44(_274) * (sign - _c0);
    }
    _bc += sub_7100791E44(_270) * (*mSideOffset_s * _c0 - _bc);
}

// NON_MATCHING: curve lifetimes, field loads and floating registers differ.
void CameraShieldSurfing::sub_71007817A0(f32 latitude, f32* out) {
    if (*mOffsetYMin_s == *mOffsetYMax_s) {
        *out = *mOffsetYMin_s;
        return;
    }
    f32 value = angleStuff(latitude);
    if (value < _228)
        value = _228;
    else if (!(value <= _22c))
        value = _22c;
    value = angleStuff(value);
    {
        act::Unk_71024741b8 curve;
        curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.eval(value);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _268, 1.0f - _26c, 1.0f, *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(*mOffsetYMax_s, *mOffsetYMax_s, *mOffsetYMin_s, *mOffsetYMin_s,
                  *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
        *out = curve.eval(value);
    }
}

// NON_MATCHING: width bounds, curve lifetimes and field loads differ.
void CameraShieldSurfing::sub_7100781548() {
    _238 = sead::Mathf::clamp(*mLatMinWidth_s, 0.0f, 0.5f);
    _23c = sead::Mathf::clamp(*mLatMaxWidth_s, 0.0f, 0.5f);
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_228, &_22c);
    sub_7100924CDC(*mLatLimitMin_s, *mLatLimitMax_s, &_230, &_234);
    _230 = angleStuff(sead::Mathf::clampMin(_230, _228));
    _234 = angleStuff(sead::Mathf::clampMax(_234, _22c));
    if (angleStuff(_228) == angleStuff(_22c)) {
        _e4 = 0.0f;
        _e8 = 0.0f;
    } else {
        f32 value;
        {
            act::Unk_71024741b8 curve;
            curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
            value = curve.sub_71009234D8(_230, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
            _e4 = curve.eval(value);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
            value = curve.sub_71009234D8(_234, 10);
        }
        {
            act::Unk_71024741b8 curve;
            curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
            _e8 = curve.eval(value);
        }
    }
    f32 value = angleStuff(*mLat_s);
    if (value < _228)
        value = _228;
    else if (!(value <= _22c))
        value = _22c;
    _240 = angleStuff(value);
}

// NON_MATCHING: polar and side-vector store scheduling differs.
void CameraShieldSurfing::sub_71007803E0(sead::Vector3f* out, const act::Unk_7100922700* polar) {
    *out = _ac;
    f32 height = 0.0f;
    if (sub_71009269F8(*out, &height)) {
        height += 0.4f;
        out->y = sead::Mathf::max(out->y, height);
    }
    f32 offset = 0.0f;
    sub_71007817A0(polar->_4, &offset);
    out->y += offset;
    if (auto* camera = getCameraActor()) {
        const sead::Vector3f base = camera->_860._270.getBase(0);
        sead::Vector3f direction(-base.x, 0.0f, -base.z);
        const f32 length = sead::Vector3f(base.x, 0.0f, base.z).length();
        if (length > 0.0f)
            direction *= _bc / length;
        *out += direction;
    }
}

// NON_MATCHING: target and projected-vector store scheduling differs.
void CameraShieldSurfing::sub_710078105C() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    sead::Vector3f target(0.0f, 0.0f, 0.0f);
    sub_71007803E0(&target, &polar);
    _94 = target;
    _a0 = camera->_860._0._c - target;
    const sead::Vector3f velocity = camera->_860._270.getTranslation() -
                                   sub_7100928868(camera->_860._164);
    sead::Vector3f axis = _a0;
    const f32 length = axis.length();
    if (length > 0.0f)
        axis *= 1.0f / length;
    sead::Vector3f projected(0.0f, 0.0f, 0.0f);
    ksys::util::sub_71011EFA54(&projected, velocity, axis);
    if (_a0.dot(projected) > 0.0f)
        projected.set(0.0f, 0.0f, 0.0f);
    if (_a0.dot(_a0 + projected) < 0.0f)
        projected = -_a0;
    _a0 += projected;
    _94 -= projected;
}

// NON_MATCHING: prepared field loads and floating registers differ.
void CameraShieldSurfing::sub_7100780ED0(bool clamp_latitude) {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    if (clamp_latitude) {
        f32 latitude = polar._4;
        if (latitude < _228)
            latitude = _228;
        else if (!(latitude <= _22c))
            latitude = _22c;
        _dc = angleStuff(latitude);
    } else {
        _dc = _240;
    }
    _e0 = angleStuff(polar._4 - _dc);
    const sead::Vector3f forward = camera->_860._270.getBase(2);
    f32 yaw_difference = 0.0f;
    if (forward.x == 0.0f && forward.z == 0.0f) {
        _f4 = polar._8;
    } else {
        const f32 yaw = (std::atan2(forward.x, forward.z) + 3.1415927f) * 57.295776f;
        _f4 = angleStuff(yaw);
        yaw_difference = polar._8 - angleStuff(yaw);
    }
    _f8 = angleStuff(yaw_difference);
    sub_710078105C();
    _100 = _25c;
    _104 = polar._0 - _25c;
    _108 = camera->_860._0._24 - _27c;
    if (!_284.isOn(1))
        _50.sub_710079C384(10.0f, 0.0f);
    _70.sub_710079C384(10.0f, 0.0f);
}

void CameraShieldSurfing::sub_71007808F4() {
    sub_7100780ED0(false);
    _70.sub_710079C3F8(1.0f);
    if (auto* camera = getCamera()) {
        const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
        const act::Unk_7100922700 current(1.0f, polar._4, polar._8);
        const act::Unk_7100922700 target(1.0f, _dc, _f4);
        sub_710074BDF8(current.sub_7100923254().dot(target.sub_7100923254()));
    }
}

// NON_MATCHING: latitude field loads and floating registers differ.
void CameraShieldSurfing::sub_71007809E0() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 difference = 0.0f;
    if (angleStuff(polar._4) < angleStuff(_228)) {
        _dc = _228;
        difference = polar._4 - _dc;
    } else if (angleStuff(_22c) < angleStuff(polar._4)) {
        _dc = _22c;
        difference = polar._4 - _dc;
    } else {
        _dc = polar._4;
    }
    _e0 = angleStuff(difference);
    _104 = 0.0f;
    _100 = polar._0;
    sub_71007812B8();
}

// NON_MATCHING: curve lifetimes, field loads and vector scheduling differ.
void CameraShieldSurfing::sub_7100780AD8() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 difference = 0.0f;
    if (angleStuff(polar._4) < angleStuff(_228)) {
        _dc = _228;
        difference = polar._4 - _dc;
    } else if (angleStuff(_22c) < angleStuff(polar._4)) {
        _dc = _22c;
        difference = polar._4 - _dc;
    } else {
        _dc = polar._4;
    }
    _e0 = angleStuff(difference);
    f32 duration = 0.0f;
    if (angleStuff(_e0) != angleStuff(0.0f))
        duration = sead::Mathf::clampMin((_e0 > 0.0f ? _e0 : -_e0) * 0.75f, 10.0f);
    _f4 = polar._8;
    _f8 = angleStuff(0.0f);
    f32 value = _dc;
    {
        act::Unk_71024741b8 curve;
        curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.eval(value);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _254, 1.0f - _258, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(_24c, _24c, _250, _250, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.eval(value);
    }
    const f32 radius_difference = polar._0 - value;
    if (!((radius_difference > 0.0f ? radius_difference : -radius_difference) > 1.4f)) {
        f32 min = 0.0f;
        f32 max = 0.0f;
        sub_7100924C94(_24c, _250, &min, &max);
        value = polar._0;
        if (value < min)
            value = min;
        else if (!(value <= max))
            value = max;
    }
    _100 = value;
    _104 = polar._0 - value;
    if (_104 != 0.0f)
        duration = sead::Mathf::clampMin(std::fmax(duration, 10.0f),
                                       (_104 > 0.0f ? _104 : -_104) * 0.5f);
    sub_710078105C();
    if (_a0 != sead::Vector3f(0.0f, 0.0f, 0.0f)) {
        const f32 length = _a0.length();
        duration = sead::Mathf::clampMin(duration, 10.0f);
        if (!(length <= 5.0f))
            duration = sead::Mathf::clampMin(duration, (length > 0.0f ? length : -length) * 2.5f);
    }
    _108 = camera->_860._0._24 - _27c;
    const f32 degrees = _108 * 57.295776f;
    duration = sead::Mathf::clampMin(duration, (degrees > 0.0f ? degrees : -degrees) * 0.5f);
    duration = sead::Mathf::clampMax(duration, 90.0f);
    if (!_284.isOn(1))
        _50.sub_710079C384(duration, 0.0f);
    _70.sub_710079C384(duration, 0.0f);
    _70.sub_710079C3F8(1.0f);
    sub_710074BCB4();
}

// NON_MATCHING: field loads, vector scheduling and floating registers differ.
void CameraShieldSurfing::sub_71007812B8() {
    auto* camera = getCamera();
    if (!camera)
        return;
    const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
    f32 duration = sub_71009226D8(_e0);
    if (duration <= 0.0f)
        duration = 0.0f;
    else
        duration = std::fmax(duration * 0.5f, 0.0f);
    const sead::Vector3f forward = camera->_860._270.getBase(2);
    f32 difference = 0.0f;
    if (forward.x == 0.0f && forward.z == 0.0f) {
        _f4 = polar._8;
    } else {
        const f32 yaw = (std::atan2(forward.x, forward.z) + 3.1415927f) * 57.295776f;
        _f4 = angleStuff(yaw);
        difference = polar._8 - angleStuff(yaw);
    }
    _f8 = angleStuff(difference);
    if (angleStuff(_f8) != angleStuff(0.0f))
        duration = sead::Mathf::max(duration, (_f8 > 0.0f ? _f8 : -_f8) * 0.25f);
    if (_104 != 0.0f)
        duration = sead::Mathf::clampMin(duration, (_104 < 0.0f ? -_104 : _104) * 2.5f);
    sub_710078105C();
    if (_a0 != sead::Vector3f(0.0f, 0.0f, 0.0f)) {
        const f32 length = _a0.length();
        if (!(length <= 5.0f))
            duration = sead::Mathf::clampMin(duration, (length > 0.0f ? length : -length) * 2.5f);
    }
    _108 = camera->_860._0._24 - _27c;
    const f32 degrees = _108 * 57.295776f;
    duration = sead::Mathf::clampMin(duration, (degrees > 0.0f ? degrees : -degrees) * 0.5f);
    if (!(duration <= 0.0f)) {
        if (duration < 10.0f)
            duration = 10.0f;
        else if (!(duration <= 90.0f))
            duration = 90.0f;
    }
    if (!_284.isOn(1))
        _50.sub_710079C384(duration, 0.0f);
    _70.sub_710079C384(duration, 0.0f);
    _70.sub_710079C3F8(_280);
    sub_710074BCB4();
}

// NON_MATCHING: curve lifetimes, field loads and scalar scheduling differ.
void CameraShieldSurfing::sub_710077EBEC() {
    sub_7100781548();
    _244 = sub_7100924D80(*mLngCus_s);
    _248 = sead::Mathf::clampMin(*mLngCusSpeedEffect_s, 0.01f);
    _24c = sub_7100924D40(*mRadiusMin_s);
    _250 = sub_7100924D40(*mRadiusMax_s);
    _254 = sead::Mathf::clamp(*mRadiusMinWidth_s, 0.0f, 0.5f);
    _258 = sead::Mathf::clamp(*mRadiusMaxWidth_s, 0.0f, 0.5f);
    _25c = sub_7100924D40(*mRadius_s);
    _278 = sub_7100924D80(*mAtHCus_s);
    sub_7100924DA4(*mAtVCusMin_s, *mAtVCusMax_s, &_260, &_264);
    _268 = sead::Mathf::clamp(*mOffsetYMinWidth_s, 0.0f, 0.5f);
    _26c = sead::Mathf::clamp(*mOffsetYMaxWidth_s, 0.0f, 0.5f);
    _27c = sub_7100924D50(*mFovy_s);
    _270 = sub_7100924D80(*mSideOffsetCus_s);
    _274 = sub_7100924D80(*mSideOffsetRateCus_s);
    _280 = sead::Mathf::clampMin(*mAutoModeConnect_s, 0.0f);
}

// NON_MATCHING: curve lifetimes, field loads and scalar scheduling differ.
void CameraShieldSurfing::sub_710077ED58() {
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
    polar._0 = _25c;
    camera->_860._0._c = camera->_860._0._0 + polar.sub_7100923254();
}

// NON_MATCHING: curve lifetimes, field loads and scalar scheduling differ.
void CameraShieldSurfing::sub_710077EF8C() {
    switch (_286) {
    case 0:
        sub_7100780ED0(false);
        _70.sub_710079C3F8(_90);
        break;
    case 1:
        sub_7100780ED0(true);
        _70.sub_710079C3F8(_90);
        break;
    case 2:
        sub_71007808F4();
        break;
    case 3:
        if (auto* camera = getCamera()) {
            const act::Unk_7100922700 polar(camera->_860._0._0 - camera->_860._0._c);
            _dc = _240;
            _e0 = angleStuff(polar._4 - _240);
            _100 = _25c;
            _104 = polar._0 - _25c;
            sub_710078105C();
        }
        break;
    case 4:
        sub_71007809E0();
        break;
    default:
        sub_7100780AD8();
        break;
    }
    _90 = 1.0f;
    _284.set(1);
}

// NON_MATCHING: curve lifetimes, field loads and scalar scheduling differ.
void CameraShieldSurfing::sub_710077FFA0() {
    if (_228 == _22c || (std::fabs(_228) == 180.0f && std::fabs(_22c) == 180.0f) ||
        _24c == _250) {
        _100 = _25c;
        return;
    }
    f32 value = _240;
    {
        act::Unk_71024741b8 curve;
        curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    f32 base_lat_ratio;
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        base_lat_ratio = curve.eval(value);
    }
    value = angleStuff(_f0 + _dc);
    if (value < _228)
        value = _228;
    else if (!(value <= _22c))
        value = _22c;
    value = angleStuff(value);
    {
        act::Unk_71024741b8 curve;
        curve.set(_228, _228, _22c, _22c, *mLatMinWeight_s, *mLatMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    f32 lat_ratio;
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _238, 1.0f - _23c, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
        lat_ratio = curve.eval(value);
    }
    const f32 edge = lat_ratio > base_lat_ratio ? 1.0f : -1.0f;
    f32 blend = 1.0f;
    if (edge - base_lat_ratio != 0.0f)
        blend = (lat_ratio - base_lat_ratio) / (edge - base_lat_ratio);
    f32 min = 1.0f;
    f32 max = 1.0f;
    sub_7100924C94(_24c, _250, &min, &max);
    value = _25c;
    if (value < min)
        value = min;
    else if (!(value <= max))
        value = max;
    {
        act::Unk_71024741b8 curve;
        curve.set(_24c, _24c, _250, _250, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.sub_71009234D8(value, 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _254, 1.0f - _258, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.eval(value);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(0.0f, _254, 1.0f - _258, 1.0f, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.sub_71009234D8(value + blend * (edge - value), 10);
    }
    {
        act::Unk_71024741b8 curve;
        curve.set(_24c, _24c, _250, _250, *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
        value = curve.eval(value);
    }
    const f32 radius = sub_7100924D40(value);
    const f32 rate = sub_7100791E44(0.6f);
    _100 += rate * (radius - _100);
}

}  // namespace uking::action
