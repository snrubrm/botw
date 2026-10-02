#include "Game/AI/AI/aiCameraEditRoot.h"

namespace uking::ai {

CameraEditRoot::CameraEditRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool CameraEditRoot::init_(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return true;
}

}  // namespace uking::ai
