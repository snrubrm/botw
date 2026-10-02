#include "Game/AI/Action/actionCameraEventAnim.h"
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

CameraEventAnim::CameraEventAnim(const InitArg& arg) : CameraEventAnimBase(arg) {}

CameraEventAnim::~CameraEventAnim() = default;

void CameraEventAnim::m46() {
    CameraEventAnimBase::m46();
    getDynamicParam_2(&mClipIndex_d, "ClipIndex");
    getDynamicParam_2(&mTargetActor_d, "TargetActor");
    getDynamicParam_2(&mTargetActorPosReferenceMode_d, "TargetActorPosReferenceMode");
    getDynamicParam_2(&mTargetActorDirReferenceMode_d, "TargetActorDirReferenceMode");
    getDynamicParam_2(&mAccept1FrameDelay_d, "Accept1FrameDelay");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

float CameraEventAnim::m49() {
    return ksys::evt::Manager::instance()->sub_7100DB1138(*mClipIndex_d);
}

u8 CameraEventAnim::m52() {
    return _1c8;
}

void CameraEventAnim::m53() {
    const int target = *mTargetActor_d;
    _1c8 = target >= -1 && target < 4 ? target : -1;
}

const sead::SafeString& CameraEventAnim::m54() {
    return mActorName_d;
}

const sead::SafeString& CameraEventAnim::m55() {
    return mUniqueName_d;
}

u8 CameraEventAnim::m56() {
    return _1c9;
}

void CameraEventAnim::m57() {
    const int mode = *mTargetActorPosReferenceMode_d;
    if (mode >= 0 && mode <= 3) {
        _1c9 = mode;
        return;
    }

    sead::FixedSafeString<128> flow;
    sead::FixedSafeString<128> entry;
    getActiveEventFlowPath_0(mActor, &flow, &entry);
    _1c9 = 1;
}

u8 CameraEventAnim::m58() {
    return _1ca;
}

void CameraEventAnim::m59() {
    const int mode = *mTargetActorDirReferenceMode_d;
    if (mode >= 0 && mode <= 3) {
        _1ca = mode;
        return;
    }

    sead::FixedSafeString<128> flow;
    sead::FixedSafeString<128> entry;
    getActiveEventFlowPath_0(mActor, &flow, &entry);
    _1ca = 3;
}

bool CameraEventAnim::m60() {
    return *mAccept1FrameDelay_d;
}

}  // namespace uking::action
