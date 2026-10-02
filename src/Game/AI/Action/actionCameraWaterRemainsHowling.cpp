#include "Game/AI/Action/actionCameraWaterRemainsHowling.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraWaterRemainsHowling::CameraWaterRemainsHowling(const InitArg& arg) : CameraAction(arg) {}

CameraWaterRemainsHowling::~CameraWaterRemainsHowling() = default;

void CameraWaterRemainsHowling::m33() {
    _100 = sub_7100924D40(*mRadius_s);
    _104 = sub_7100924D50(*mFovy_s);
    _108 = sead::Mathf::clamp(_108, 0.0f, 1.0f);
    _10c = 1.0f - _108;
    sub_710078BF18();
    sub_710078C1F0();
    _110 = false;
}

void CameraWaterRemainsHowling::m36() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusFromPlayer_s, "RadiusFromPlayer");
    getStaticParam(&mAtY_s, "AtY");
    getStaticParam(&mAtOffsetZ_s, "AtOffsetZ");
    getStaticParam(&mWaterAvoid4At_s, "WaterAvoid4At");
    getStaticParam(&mWaterAvoid4CameraPos_s, "WaterAvoid4CameraPos");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mConnect_s, "Connect");
}

}  // namespace uking::action
