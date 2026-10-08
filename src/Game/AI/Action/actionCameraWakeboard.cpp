#include "Game/AI/Action/actionCameraWakeboard.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>

namespace uking::action {

CameraWakeboard::CameraWakeboard(const InitArg& arg) : CameraAction(arg) {}

CameraWakeboard::~CameraWakeboard() = default;

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
    f32 value = angleStuff(sead::Mathf::clamp(angleStuff(latitude), _258, _25c));
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
    value = angleStuff(sead::Mathf::clamp(angleStuff(_ec + _d8), _258, _25c));
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
    value = sead::Mathf::clamp(_28c, min, max);
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
        value = sead::Mathf::clamp(polar._0, min, max);
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
