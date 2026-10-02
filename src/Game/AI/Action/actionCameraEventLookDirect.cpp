#include "Game/AI/Action/actionCameraEventLookDirect.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

CameraEventLookDirect::CameraEventLookDirect(const InitArg& arg) : CameraEventLookBase(arg) {}

void CameraEventLookDirect::m46() {
    CameraEventLookBase::m46();
    getDynamicParam_2(&mPosX_d, "PosX");
    getDynamicParam_2(&mPosY_d, "PosY");
    getDynamicParam_2(&mPosZ_d, "PosZ");
    getDynamicParam_2(&mDirX_d, "DirX");
    getDynamicParam_2(&mDirY_d, "DirY");
    getDynamicParam_2(&mDirZ_d, "DirZ");
}

void CameraEventLookDirect::m48(sead::Matrix34f* mtx) {
    const sead::Vector3f rotation(sead::Mathf::deg2rad(*mDirX_d), sead::Mathf::deg2rad(*mDirY_d),
                                  sead::Mathf::deg2rad(*mDirZ_d));
    mtx->makeR(rotation);
    mtx->setTranslation({*mPosX_d, *mPosY_d, *mPosZ_d});
}

}  // namespace uking::action
