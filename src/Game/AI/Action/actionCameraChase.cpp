#include "Game/AI/Action/actionCameraChase.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCameraUtil.h"

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

}  // namespace uking::action
