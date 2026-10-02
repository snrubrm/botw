#include "Game/AI/Action/actionCameraEventAnimFlow.h"
#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

CameraEventAnimFlow::CameraEventAnimFlow(const InitArg& arg) : CameraEventAnimFlowBase(arg) {}

void CameraEventAnimFlow::m46() {
    CameraEventAnimFlowBase::m46();
    getDynamicParam_2(&mTargetActor_d, "TargetActor");
    getDynamicParam_2(&mTargetActorPosReferenceMode_d, "TargetActorPosReferenceMode");
    getDynamicParam_2(&mTargetActorDirReferenceMode_d, "TargetActorDirReferenceMode");
    getDynamicParam_2(&mAccept1FrameDelay_d, "Accept1FrameDelay");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

u8 CameraEventAnimFlow::m52() {
    return _1c0;
}

void CameraEventAnimFlow::m53() {
    const int target = *mTargetActor_d;
    _1c0 = target >= -1 && target < 4 ? target : -1;
}

const sead::SafeString& CameraEventAnimFlow::m54() {
    return mActorName_d;
}

const sead::SafeString& CameraEventAnimFlow::m55() {
    return mUniqueName_d;
}

u8 CameraEventAnimFlow::m56() {
    return _1c1;
}

void CameraEventAnimFlow::m57() {
    const int mode = *mTargetActorPosReferenceMode_d;
    if (mode >= 0 && mode <= 3) {
        _1c1 = mode;
        return;
    }

    sead::FixedSafeString<128> flow;
    sead::FixedSafeString<128> entry;
    getActiveEventFlowPath_0(mActor, &flow, &entry);
    _1c1 = 1;
}

u8 CameraEventAnimFlow::m58() {
    return _1c2;
}

void CameraEventAnimFlow::m59() {
    const int mode = *mTargetActorDirReferenceMode_d;
    if (mode >= 0 && mode <= 3) {
        _1c2 = mode;
        return;
    }

    sead::FixedSafeString<128> flow;
    sead::FixedSafeString<128> entry;
    getActiveEventFlowPath_0(mActor, &flow, &entry);
    _1c2 = 3;
}

bool CameraEventAnimFlow::m60() {
    return *mAccept1FrameDelay_d;
}

}  // namespace uking::action
