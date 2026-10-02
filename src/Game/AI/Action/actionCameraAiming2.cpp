#include "Game/AI/Action/actionCameraAiming2.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraAiming2::CameraAiming2(const InitArg& arg) : CameraAction(arg) {}

CameraAiming2::~CameraAiming2() = default;

// NON_MATCHING: the original evaluates the clamps branch-free (fcsel / fccmp)
void CameraAiming2::sub_710074EC10() {
    sub_7100924CDC(*mLatMin_s, *mLatMax_s, &_278, &_27c);
    _280 = sead::Mathf::clamp(*mLatMinWidth_s, 0.0f, 0.5f);
    _284 = sead::Mathf::clamp(*mLatMaxWidth_s, 0.0f, 0.5f);
    _288 = sub_7100924D40(*mRadiusMin_s);
    _28c = sub_7100924D40(*mRadiusMax_s);
    _290 = sead::Mathf::clamp(*mRadiusMinWidth_s, 0.0f, 0.5f);
    _294 = sead::Mathf::clamp(*mRadiusMaxWidth_s, 0.0f, 0.5f);
    _298 = sead::Mathf::clamp(*mOffsetYMinWidth_s, 0.0f, 0.5f);
    _29c = sead::Mathf::clamp(*mOffsetYMaxWidth_s, 0.0f, 0.5f);
    _2a0 = sub_7100924D50(*mFovy_s);
    const u32 gyro = *mGyro_s;
    _2a4 = gyro > 2 ? 0 : gyro;
}

void CameraAiming2::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraAiming2::m36() {
    getStaticParam(&mLatMin_s, "LatMin");
    getStaticParam(&mLatMax_s, "LatMax");
    getStaticParam(&mLatMinWidth_s, "LatMinWidth");
    getStaticParam(&mLatMaxWidth_s, "LatMaxWidth");
    getStaticParam(&mLatMinWeight_s, "LatMinWeight");
    getStaticParam(&mLatMaxWeight_s, "LatMaxWeight");
    getStaticParam(&mLatStickScale_s, "LatStickScale");
    getStaticParam(&mLngStickScale_s, "LngStickScale");
    getStaticParam(&mLatGyroScale_s, "LatGyroScale");
    getStaticParam(&mLngGyroScale_s, "LngGyroScale");
    getStaticParam(&mRadiusMin_s, "RadiusMin");
    getStaticParam(&mRadiusMax_s, "RadiusMax");
    getStaticParam(&mRadiusMinWidth_s, "RadiusMinWidth");
    getStaticParam(&mRadiusMaxWidth_s, "RadiusMaxWidth");
    getStaticParam(&mRadiusMinWeight_s, "RadiusMinWeight");
    getStaticParam(&mRadiusMaxWeight_s, "RadiusMaxWeight");
    getStaticParam(&mSideOffset_s, "SideOffset");
    getStaticParam(&mOffsetYMin_s, "OffsetYMin");
    getStaticParam(&mOffsetYMax_s, "OffsetYMax");
    getStaticParam(&mOffsetYMinWidth_s, "OffsetYMinWidth");
    getStaticParam(&mOffsetYMaxWidth_s, "OffsetYMaxWidth");
    getStaticParam(&mOffsetYMinWeight_s, "OffsetYMinWeight");
    getStaticParam(&mOffsetYMaxWeight_s, "OffsetYMaxWeight");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mGyro_s, "Gyro");
    getStaticParam(&mConnect_s, "Connect");
}

void CameraAiming2::sub_7100750334(f32* out) {
    f32 offset = *mOffsetYMin_s;
    if (_278 != _27c || *mOffsetYMin_s == *mOffsetYMax_s) {
        if (*mOffsetYMin_s != *mOffsetYMax_s) {
            const f32 lat = _4c;
            f32 t;
            {
                act::Unk_71024741b8 curve;
                curve.set(_278, _278, _27c, _27c, *mLatMinWeight_s, *mLatMaxWeight_s);
                t = curve.sub_71009234D8(lat, 10);
                act::Unk_71024741b8 rate_curve;
                rate_curve.set(0.0f, _280, 1.0f - _284, 1.0f, *mLatMinWeight_s, *mLatMaxWeight_s);
                t = rate_curve.eval(t);
            }
            {
                act::Unk_71024741b8 rate_curve;
                rate_curve.set(0.0f, _298, 1.0f - _29c, 1.0f, *mOffsetYMaxWeight_s,
                               *mOffsetYMinWeight_s);
                t = rate_curve.sub_71009234D8(t, 10);
                act::Unk_71024741b8 curve;
                curve.set(*mOffsetYMax_s, *mOffsetYMax_s, *mOffsetYMin_s, *mOffsetYMin_s,
                          *mOffsetYMaxWeight_s, *mOffsetYMinWeight_s);
                offset = curve.eval(t);
            }
        }
    } else {
        offset = (*mOffsetYMin_s + *mOffsetYMax_s) * 0.5f;
    }
    *out = offset;
}

}  // namespace uking::action
