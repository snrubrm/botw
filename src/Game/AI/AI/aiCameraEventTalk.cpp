#include "Game/AI/AI/aiCameraEventTalk.h"

namespace uking::ai {

// NON_MATCHING: the original stores _5c and _60.._63 with one stp of two words (one 8-byte store here)
CameraEventTalk::CameraEventTalk(const InitArg& arg) : CameraEvent(arg) {}

f32 CameraEventTalk::m45() {
    return 0.0f;
}

bool CameraEventTalk::m46() {
    return false;
}

bool CameraEventTalk::m48() {
    return m47() == 0.0f;
}

void CameraEventTalk::m50() {}

bool CameraEventTalk::isFinished() const {
    if (mFlags.isOn(Flag::Finished))
        return true;
    if (auto* child = getCurrentChild()) {
        if (child->isFinished())
            return true;
        if (child->isFailed())
            return false;
    }
    return false;
}

}  // namespace uking::ai
