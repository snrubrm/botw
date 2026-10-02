#include "Game/AI/AI/aiCameraRoot.h"

namespace uking::ai {

CameraRoot::CameraRoot(const InitArg& arg) : CameraAI(arg) {}

CameraRoot::~CameraRoot() = default;

bool CameraRoot::m34(sead::Heap* heap) {
    mFlags.set(Flag::Changeable);
    return true;
}

}  // namespace uking::ai
