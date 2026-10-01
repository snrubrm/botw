#include "Game/AI/AI/aiCameraBow.h"

namespace uking::ai {

CameraBow::CameraBow(const InitArg& arg) : CameraAI(arg) {}

bool CameraBow::m34(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return true;
}

}  // namespace uking::ai
