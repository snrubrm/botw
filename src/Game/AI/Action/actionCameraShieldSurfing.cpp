#include "Game/AI/Action/actionCameraShieldSurfing.h"
#include "KingSystem/Utils/MathUtil.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/System/Timer.h"

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
