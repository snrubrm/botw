#include "Game/AI/Action/actionCameraRumbleStop.h"
#include "KingSystem/System/Vibration.h"

namespace uking::action {

CameraRumbleStop::CameraRumbleStop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool CameraRumbleStop::oneShot_() {
    if (*mCamVibId_a != -1) {
        const s32 id = *mCamVibId_a;
        *mCamVibId_a = -1;
        if (auto* vibration = ksys::Vibration::instance())
            vibration->sub_71010BB810(id);
    }
    return true;
}

void CameraRumbleStop::loadParams_() {
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

}  // namespace uking::action
