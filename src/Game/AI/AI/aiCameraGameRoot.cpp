#include "Game/AI/AI/aiCameraGameRoot.h"

namespace uking::ai {

CameraGameRoot::CameraGameRoot(const InitArg& arg) : CameraAI(arg) {}

void CameraGameRoot::m36() {
    auto* camera = getCamera();
    if (!camera || camera->_860._804.sub_710079ADC8(1))
        return;

    if (!getCurrentChild())
        changeChild("ルートAI");
}

}  // namespace uking::ai
