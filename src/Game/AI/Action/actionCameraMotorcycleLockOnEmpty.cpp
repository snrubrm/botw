#include "Game/AI/Action/actionCameraMotorcycleLockOnEmpty.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraMotorcycleLockOnEmpty::CameraMotorcycleLockOnEmpty(const InitArg& arg) : CameraAction(arg) {}

CameraMotorcycleLockOnEmpty::~CameraMotorcycleLockOnEmpty() = default;

void CameraMotorcycleLockOnEmpty::m35() {
    if (auto* camera = getCamera())
        camera->_860._7f8.reset(1);
}

void CameraMotorcycleLockOnEmpty::m36() {
    getStaticParam(&mSpeedMax_s, "SpeedMax");
    getStaticParam(&mSpeedMin_s, "SpeedMin");
    getStaticParam(&mLatitudeMin_s, "LatitudeMin");
    getStaticParam(&mLatitudeMax_s, "LatitudeMax");
    getStaticParam(&mAutoLatitudeSlow_s, "AutoLatitudeSlow");
    getStaticParam(&mAutoLatitudeFast_s, "AutoLatitudeFast");
    getStaticParam(&mAutoLatitudeB2ICushion_s, "AutoLatitudeB2ICushion");
    getStaticParam(&mAutoLngBaseCushion_s, "AutoLngBaseCushion");
    getStaticParam(&mAutoLngMaxRotSpeed_s, "AutoLngMaxRotSpeed");
    getStaticParam(&mCameraRadiusSlow_s, "CameraRadiusSlow");
    getStaticParam(&mCameraRadiusFast_s, "CameraRadiusFast");
    getStaticParam(&mCameraRadiusB2ICushion_s, "CameraRadiusB2ICushion");
    getStaticParam(&mCameraFollowRotCushion_s, "CameraFollowRotCushion");
    getStaticParam(&mCameraFollowPosCushionX_s, "CameraFollowPosCushionX");
    getStaticParam(&mCameraFollowPosCushionYUp_s, "CameraFollowPosCushionYUp");
    getStaticParam(&mCameraFollowPosCushionYDown_s, "CameraFollowPosCushionYDown");
    getStaticParam(&mCameraFollowPosCushionZ_s, "CameraFollowPosCushionZ");
    getStaticParam(&mFovySlow_s, "FovySlow");
    getStaticParam(&mFovyFast_s, "FovyFast");
    getStaticParam(&mFovyBaseCushion_s, "FovyBaseCushion");
    getStaticParam(&mSwitchingCushionRate_s, "SwitchingCushionRate");
    getStaticParam(&mAtOffsetWorld_s, "AtOffsetWorld");
    getStaticParam(&mAtOffsetLocal_s, "AtOffsetLocal");
}

}  // namespace uking::action
