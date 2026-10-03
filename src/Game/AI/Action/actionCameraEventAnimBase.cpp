#include "Game/AI/Action/actionCameraEventAnimBase.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

CameraEventAnimBase::CameraEventAnimBase(const InitArg& arg) : CameraEvent(arg) {}

// NON_MATCHING: the original null-checks the message reference (cbz x1)
bool CameraEventAnimBase::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x8800007)
        return false;
    sub_7100757A78();
    if (_90 == 2)
        sub_7100757C24();
    return true;
}

void CameraEventAnimBase::m45() {
    if (auto* camera = getCamera())
        camera->sub_7100799920();
}

void CameraEventAnimBase::m46() {
    getDynamicParam(&mSceneName_d, "SceneName");
    getDynamicParam(&mCameraName_d, "CameraName");
    getDynamicParam_2(&mStartFrame_d, "StartFrame");
    getDynamicParam_2(&mEndFrame_d, "EndFrame");
    getDynamicParam_2(&mDOFStartFrame_d, "DOFStartFrame");
    getDynamicParam_2(&mFocalLength_d, "FocalLength");
    getDynamicParam_2(&mAperture_d, "Aperture");
    getDynamicParam_2(&mDOFBlurStart_d, "DOFBlurStart");
    getDynamicParam_2(&mDOFEndFrame_d, "DOFEndFrame");
    getDynamicParam_2(&mFocalLengthEnd_d, "FocalLengthEnd");
    getDynamicParam_2(&mApertureEnd_d, "ApertureEnd");
    getDynamicParam_2(&mDOFBlurEnd_d, "DOFBlurEnd");
    getDynamicParam_2(&mOverwriteAtDist_d, "OverwriteAtDist");
    getDynamicParam_2(&mInterpolateCount_d, "InterpolateCount");
    getDynamicParam_2(&mDOFUse_d, "DOFUse");
    getDynamicParam_2(&mOverwriteAt_d, "OverwriteAt");
    getDynamicParam_2(&mBgCheck_d, "BgCheck");
}

void CameraEventAnimBase::m47() {}

void CameraEventAnimBase::m48() {}

float CameraEventAnimBase::m49() {
    return 0.0f;
}

void CameraEventAnimBase::m50(sead::BufferedSafeString* out) {
    out->copy(mSceneName_d);
}

u8 CameraEventAnimBase::m52() {
    return -1;
}

void CameraEventAnimBase::m53() {}

const sead::SafeString& CameraEventAnimBase::m54() {
    return sead::SafeString::cEmptyString;
}

const sead::SafeString& CameraEventAnimBase::m55() {
    return sead::SafeString::cEmptyString;
}

u8 CameraEventAnimBase::m56() {
    return 3;
}

void CameraEventAnimBase::m57() {}

u8 CameraEventAnimBase::m58() {
    return 3;
}

void CameraEventAnimBase::m59() {}

bool CameraEventAnimBase::m60() {
    return false;
}

}  // namespace uking::action
