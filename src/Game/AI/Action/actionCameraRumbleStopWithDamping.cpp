#include "Game/AI/Action/actionCameraRumbleStopWithDamping.h"
#include "KingSystem/System/Vibration.h"

namespace uking::action {

CameraRumbleStopWithDamping::CameraRumbleStopWithDamping(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

bool CameraRumbleStopWithDamping::oneShot_() {
    if (*mCamVibId_a != -1) {
        const s32 id = *mCamVibId_a;
        *mCamVibId_a = -1;
        if (auto* vibration = ksys::Vibration::instance())
            vibration->sub_71010BB82C(id, *mDampingTime_d);
    }
    return true;
}

void CameraRumbleStopWithDamping::loadParams_() {
    getDynamicParam_2(&mDampingTime_d, "DampingTime");
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

}  // namespace uking::action
