#include "Game/AI/Action/actionCameraShieldSurfing.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

CameraShieldSurfing::CameraShieldSurfing(const InitArg& arg) : CameraAction(arg) {}

CameraShieldSurfing::~CameraShieldSurfing() = default;

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

}  // namespace uking::action
