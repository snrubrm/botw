#include "Game/AI/Behavior/behaviorCameraNotify2Sound.h"

namespace uking::behavior {

CameraNotify2Sound::CameraNotify2Sound(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void CameraNotify2Sound::loadParams() {
    getStaticParam(&mCameraStateNotify2Sound_s, "CameraStateNotify2Sound");
}

}  // namespace uking::behavior
