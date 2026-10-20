#include "Game/Actor/Camera/Action/actionCameraChase.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectCamera.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

CameraChase::CameraChase(const InitArg& arg) : CameraAction(arg) {}

CameraChase::~CameraChase() = default;

void CameraChase::sub_710075165C() {
    switch (_2bb) {
    case 0:
        sub_7100753AA0();
        break;
    case 1:
        sub_7100753EA4();
        break;
    case 2:
        sub_7100754194();
        break;
    case 4:
        sub_7100754680();
        break;
    default:
        sub_7100754A0C();
        break;
    }

    _70.sub_710079C3F8(_90);
    if (!_2b8.isOn(1))
        _50.sub_710079C57C(_70);
    _90 = 1.0f;
    _2b8.reset(9);
    _2b8.set(1);
}

// NON_MATCHING: scheduling (the original computes 1 - a in both branches)
f32 CameraChase::sub_7100752FA4(f32 value) {
    const f32 stick = sead::Mathf::clamp(value, -1.0f, 1.0f);
    const f32 progress = sub_7100791E44(_2a4);

    f32 a, b, factor;
    if (stick > 0.0f) {
        a = sub_71009220B4();
        b = sub_71009220C0();
        factor = 1.0f - stick;
    } else {
        a = sub_71009220CC();
        b = sub_71009220D8();
        factor = stick + 1.0f;
    }

    const f32 first = sead::Mathf::clamp(factor * (1.0f - a) + a, 0.0f, 1.0f);
    const f32 second = sead::Mathf::clamp(b + (1.0f - b) * factor, 0.0f, 1.0f);
    return progress * first * second;
}

// NON_MATCHING: the original clamps the widths with branch-free selects (ours: branches)
f32 CameraChase::sub_7100753084(f32 value) {
    act::Unk_71024741b8 curve1;
    curve1.set(0.0f, sead::Mathf::clamp(*mLatMinWidth_s, 0.0f, 0.5f),
               1.0f - sead::Mathf::clamp(*mLatMaxWidth_s, 0.0f, 0.5f), 1.0f, *mLatMinWeight_s,
               *mLatMaxWeight_s);
    const f32 t = curve1.sub_71009234D8(value, 10);

    act::Unk_71024741b8 curve2;
    curve2.set(_f4, _f4, _f8, _f8, *mLatMinWeight_s, *mLatMaxWeight_s);
    return curve2.eval(t);
}

// NON_MATCHING: the original clamps the widths with branch-free selects (ours: branches)
f32 CameraChase::sub_71007517E8(f32 value) {
    act::Unk_71024741b8 curve1;
    curve1.set(0.0f, sead::Mathf::clamp(*mOffsetYMinWidth_s, 0.0f, 0.5f),
               1.0f - sead::Mathf::clamp(*mOffsetYMaxWidth_s, 0.0f, 0.5f), 1.0f,
               *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
    const f32 t = curve1.sub_71009234D8(value, 10);

    act::Unk_71024741b8 curve2;
    curve2.set(*mOffsetYMax_s, *mOffsetYMax_s, *mOffsetYMin_s, *mOffsetYMin_s,
               *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
    return curve2.eval(t);
}

// NON_MATCHING: the ground height gets its own stack slot (the original reuses the offset vector's).
void CameraChase::sub_71007534B8(sead::Vector3f* out, const sead::Vector3f* angles) {
    ksys::act::acc::PlayerBase accessor;
    sub_7100926A50(&accessor);
    if (!accessor.hasProc())
        return;

    out->x = _ac.x;
    out->y = _ac.y;
    out->z = _ac.z;
    f32 ground_height = 0.0f;
    if (sub_71009269F8(*out, &ground_height)) {
        ground_height += accessor.m188() ? 0.05f : 0.4f;
        out->y = sead::Mathf::max(out->y, ground_height);
    }

    sead::Vector3f offset = sead::Vector3f::zero;
    sub_7100755108(&offset, angles);
    *out += offset;

    if (*mOffsetYMin_s == *mOffsetYMax_s) {
        out->y += *mOffsetYMin_s;
    } else {
        const f32 lat = sead::Mathf::clamp(angleStuff(angles->y), _f4, _f8);
        out->y += sub_71007517E8(sub_7100751710(angleStuff(lat)));
    }
}

// NON_MATCHING: the original shares one epilogue between the early return and the main path and
// keeps the radius in the first operand of the two clamp selects; ours duplicates the epilogue and
// swaps the select operands. Every value and call is the same.
// 0x7100754f00 (placeholder name): the radius blend for the lat angle. The lat and _104 are
// clamped into the lat range and mapped through the lat curve; the fraction between the two curve
// values lerps the clamped radius towards +-1 and the result goes back through the radius curve.
f32 CameraChase::sub_7100754F00() {
    if (_f4 == _f8 || _140 == _144)
        return _2a8;

    f32 min = 0.0f;
    f32 max = 0.0f;
    sub_7100924C94(_f4, _f8, &min, &max);

    const f32 base = sub_7100751710(sead::Mathf::clamp(_2a0, min, max));
    const f32 target = sub_7100751710(sead::Mathf::clamp(_104, min, max));

    const f32 edge = base < target ? 1.0f : -1.0f;
    f32 blend = 1.0f;
    if (edge - base != 0.0f)
        blend = (target - base) / (edge - base);

    f32 rmin = 1.0f;
    f32 rmax = 1.0f;
    sub_7100924C94(_140, _144, &rmin, &rmax);
    const f32 radius = sead::Mathf::clampMin(sead::Mathf::clampMax(_2a8, rmax), rmin);

    const f32 curve = sub_7100752EB8(radius);
    return sub_7100924D40(sub_710075315C(curve + blend * (edge - curve)));
}

// NON_MATCHING: the original clamps the widths with branch-free selects (ours: branches)
f32 CameraChase::sub_7100752EB8(f32 value) {
    act::Unk_71024741b8 curve1;
    const f32 min_radius = sead::Mathf::clampMin(_140, 0.01f);
    const f32 max_radius = sead::Mathf::clampMin(_144, 0.01f);
    curve1.set(min_radius, min_radius, max_radius, max_radius, *mRadiusMinWeight_s,
               *mRadiusMaxWeight_s);
    const f32 t = curve1.sub_71009234D8(value, 10);

    act::Unk_71024741b8 curve2;
    curve2.set(0.0f, sead::Mathf::clamp(*mRadiusMinWidth_s, 0.0f, 0.5f),
               1.0f - sead::Mathf::clamp(*mRadiusMaxWidth_s, 0.0f, 0.5f), 1.0f,
               *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
    return curve2.eval(t);
}

// NON_MATCHING: the original clamps the widths with branch-free selects (ours: branches)
f32 CameraChase::sub_710075315C(f32 value) {
    act::Unk_71024741b8 curve1;
    curve1.set(0.0f, sead::Mathf::clamp(*mRadiusMinWidth_s, 0.0f, 0.5f),
               1.0f - sead::Mathf::clamp(*mRadiusMaxWidth_s, 0.0f, 0.5f), 1.0f,
               *mRadiusMinWeight_s, *mRadiusMaxWeight_s);
    const f32 t = curve1.sub_71009234D8(value, 10);

    act::Unk_71024741b8 curve2;
    const f32 min_radius = sead::Mathf::clampMin(_140, 0.01f);
    const f32 max_radius = sead::Mathf::clampMin(_144, 0.01f);
    curve2.set(min_radius, min_radius, max_radius, max_radius, *mRadiusMinWeight_s,
               *mRadiusMaxWeight_s);
    return curve2.eval(t);
}

// NON_MATCHING: the original clamps the two widths with branch-free selects (ours: branches)
f32 CameraChase::sub_7100751710(f32 value) {
    act::Unk_71024741b8 curve1;
    curve1.set(_f4, _f4, _f8, _f8, *mLatMinWeight_s, *mLatMaxWeight_s);
    const f32 t = curve1.sub_71009234D8(value, 10);

    act::Unk_71024741b8 curve2;
    const f32 a = sead::Mathf::clamp(*mLatMinWidth_s, 0.0f, 0.5f);
    const f32 b = sead::Mathf::clamp(*mLatMaxWidth_s, 0.0f, 0.5f);
    curve2.set(0.0f, a, 1.0f - b, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
    return curve2.eval(t);
}

void CameraChase::m36() {
    getStaticParam(&mLatMin_s, "latMin");
    getStaticParam(&mLatMax_s, "latMax");
    getStaticParam(&mLatLimitMin_s, "LatLimitMin");
    getStaticParam(&mLatLimitMax_s, "LatLimitMax");
    getStaticParam(&mLatMinWidth_s, "LatMinWidth");
    getStaticParam(&mLatMaxWidth_s, "LatMaxWidth");
    getStaticParam(&mLatMinWeight_s, "LatMinWeight");
    getStaticParam(&mLatMaxWeight_s, "LatMaxWeight");
    getStaticParam(&mLat_s, "lat");
    getStaticParam(&mLngCus_s, "lngCus");
    getStaticParam(&mLngCusSpeedEffect_s, "lngCusSpeedEffect");
    getStaticParam(&mLatStickScale_s, "latStickScale");
    getStaticParam(&mLngStickScale_s, "lngStickScale");
    getStaticParam(&mRadiusMin_s, "radiusMin");
    getStaticParam(&mRadiusMax_s, "radiusMax");
    getStaticParam(&mRadiusMinWidth_s, "RadiusMinWidth");
    getStaticParam(&mRadiusMaxWidth_s, "RadiusMaxWidth");
    getStaticParam(&mRadiusMinWeight_s, "RadiusMinWeight");
    getStaticParam(&mRadiusMaxWeight_s, "RadiusMaxWeight");
    getStaticParam(&mRadius_s, "radius");
    getStaticParam(&mAtMoveOffset_s, "atMoveOffset");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mOffsetYMinWidth_s, "OffsetYMinWidth");
    getStaticParam(&mOffsetYMaxWidth_s, "OffsetYMaxWidth");
    getStaticParam(&mOffsetYMinWeight_s, "OffsetYMinWeight");
    getStaticParam(&mOffsetYMaxWeight_s, "OffsetYMaxWeight");
    getStaticParam(&mAtHCusMin_s, "AtHCusMin");
    getStaticParam(&mAtHCusMax_s, "AtHCusMax");
    getStaticParam(&mAtVCusMin_s, "atVCusMin");
    getStaticParam(&mAtVCusMax_s, "atVCusMax");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mConnect_s, "Connect");
    getStaticParam(&mConnectItem_s, "ConnectItem");
    getStaticParam(&mConnectIndoor_s, "ConnectIndoor");
    getStaticParam(&mProcMode_s, "ProcMode");
    getStaticParam(&mControlMode_s, "controlMode");
    getStaticParam(&mBgCheckToAt_s, "BgCheckToAt");
    getStaticParam(&mKeepManual_s, "keepManual");
}

// NON_MATCHING: load order only (the original loads _f4 / _f8 together before the first angleStuff call).
// NON_MATCHING: the clamps against 0 become fcmp + fcsel (the original uses fmax, as it does for the 0.01 clamp)
void CameraChase::sub_7100750F30() {
    sub_710075503C();
    const f32 lng_cus_speed_effect = *mLngCusSpeedEffect_s;
    _134 = lng_cus_speed_effect <= 0.01f ? 0.01f : lng_cus_speed_effect;
    _140 = sub_7100924D40(*mRadiusMin_s);
    _144 = sub_7100924D40(*mRadiusMax_s);
    const f32 at_move_offset = *mAtMoveOffset_s;
    _c4 = at_move_offset <= 0.0f ? 0.0f : at_move_offset;
    sub_7100924DA4(*mAtHCusMin_s, *mAtHCusMax_s, &_ec, &_f0);
    _2a0 = sub_7100924CAC(*mLat_s);
    _2a4 = sub_7100924D80(*mLngCus_s);
    _2a8 = sub_7100924D40(*mRadius_s);
    _2ac = sub_7100924D50(*mFovy_s);
    sub_7100924DA4(*mAtVCusMin_s, *mAtVCusMax_s, &_2b0, &_2b4);
    const f32 connect = *mConnect_s;
    _11c = connect <= 0.0f ? 0.0f : connect;
    const f32 connect_item = *mConnectItem_s;
    _120 = connect_item <= 0.0f ? 0.0f : connect_item;
    const f32 connect_indoor = *mConnectIndoor_s;
    _124 = connect_indoor <= 0.0f ? 0.0f : connect_indoor;
}

void CameraChase::sub_710075503C() {
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_f4, &_f8);
    sub_7100924CDC(*mLatLimitMin_s, *mLatLimitMax_s, &_fc, &_100);
    _fc = angleStuff(_fc < _f4 ? _f4 : _fc);
    _100 = angleStuff(_100 > _f8 ? _f8 : _100);
    if (angleStuff(_f4) != angleStuff(_f8)) {
        _10c = sub_7100751710(_fc);
        _110 = sub_7100751710(_100);
    } else {
        _10c = 0.0f;
        _110 = 0.0f;
    }
}

void CameraChase::sub_7100752DC4() {
    sead::Vector3f target = sead::Vector3f::zero;
    if (auto* camera = getCamera()) {
        const bool flag = camera->_860._7fc.sub_710079C0CC(0x40000);
        auto* c = getCamera();
        if (flag) {
            if (c)
                target = c->_860._414.getTranslation();
        } else if (c) {
            target = c->_860._2b8;
        }
    }
    const f32 rate_xz = sub_7100791E44(_dc);
    const f32 rate_y = sub_7100791E44(_e0);
    _ac.x += rate_xz * (target.x - _ac.x);
    _ac.y += rate_y * (target.y - _ac.y);
    _ac.z += rate_xz * (target.z - _ac.z);
}

bool CameraChase::sub_71007552B0() {
    if (_2be > 1)
        return false;

    ksys::act::acc::PlayerBase player;
    sub_7100926A50(&player);
    if (player.hasProc() && !player.m194() && !player.m188()) {
        if (auto* camera = getCameraActor())
            return camera->_860._270.m[1][3] - sub_7100928868(camera->_860._164).y > 0.0f;
    }
    return false;
}

void CameraChase::sub_7100752B60() {
    if (!_2b8.isOn(2)) {
        if (sub_71007552B0())
            _2b8.set(2);
    } else if (_2be >= 2) {
        _2b8.reset(2);
    } else {
        ksys::act::acc::PlayerBase player;
        sub_7100926A50(&player);
        if (!player.hasProc() || player.m194() || player.m188()) {
            _2b8.reset(2);
        } else if (auto* camera = getCamera()) {
            if (camera->_860._270.m[1][3] < _160)
                _2b8.reset(2);
        }
    }
}

void CameraChase::sub_710075156C() {
    _90 = 1.0f;
    auto* camera = getCamera();
    if (!camera)
        return;

    if (_2bb == 0 && camera->_860._80f.sub_710079C1F4(1) && camera->_860.sub_710079BF20()) {
        _90 = camera->_860._7e4;
        return;
    }

    if (camera->_860._817 <= 3) {
        if (auto* param = sub_7100791DE8())
            _90 = param->mDefaultConnectScaleAfterEvent.ref();
        return;
    }

    if (_2b8.isOn(1))
        _90 = 1.0f;
    else if (camera->_860._7fc.sub_710079C0CC(0x20000))
        _90 = _120;
    else
        _90 = camera->_860._808.sub_710079AE50(0x40) ? _124 : _11c;
}

// NON_MATCHING: the state machine's store block is laid out differently (ours shares one store, the
// original keeps it in the two changing paths) and the original clamps the timer with two compares
// and a select where ours uses fmin / fmax. The values and the branches are the same.
// 0x7100752c2c (placeholder name): moves the delay state (_2bd) from 0 to 1 and 1 to 2 when the
// timer (_150) passes 12, resets the timer on a state change and otherwise advances it towards 150 by
// the current core's delta frame. _154 is the timer's fraction of 12, clamped to 0..1.
void CameraChase::sub_7100752C2C() {
    const u8 state = _2bd;
    u8 next = state;
    if (state == 0) {
        if (_150 > 12.0f)
            next = 1;
    } else if (state == 1) {
        if (_150 > 12.0f)
            next = 2;
    }

    _2bd = next;
    if (state != next) {
        _150 = 0.0f;
    } else {
        const f32 delta = ksys::VFR::instance()->getDeltaFrame();
        if (_150 < 150.0f)
            _150 = sead::Mathf::clampMax(_150 + delta, 150.0f);
        else if (_150 > 150.0f)
            _150 = sead::Mathf::clampMin(_150 - delta, 150.0f);
    }

    f32 value;
    if (_2bd == 1) {
        _154 = _150 / 12.0f;
        value = sead::Mathf::clamp(_154, 0.0f, 1.0f);
    } else if (_2bd == 0) {
        value = 0.0f;
    } else {
        value = 1.0f;
    }
    _154 = value;
}

}  // namespace uking::action
