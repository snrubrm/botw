#include "Game/AI/Behavior/behaviorCameraNotify2Sound.h"

namespace uking::behavior {

CameraNotify2Sound::CameraNotify2Sound(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

bool CameraNotify2Sound::m6(sead::Heap* heap) {
    const u32 state = *mCameraStateNotify2Sound_s;
    _30 = state < 4 ? state : 0;
    return true;
}

void CameraNotify2Sound::loadParams() {
    getStaticParam(&mCameraStateNotify2Sound_s, "CameraStateNotify2Sound");
}

}  // namespace uking::behavior
