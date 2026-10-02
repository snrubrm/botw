#include "Game/AI/AI/aiCameraEventTalkAI.h"

namespace uking::ai {

CameraEventTalkAI::CameraEventTalkAI(const InitArg& arg) : CameraEventTalk(arg) {}

void CameraEventTalkAI::m43() {
    getStaticParam(&_68, "HeightOffset");
    getDynamicParam_2(&_70, "CameraReset");
    getDynamicParam_2(&_78, "NoConnect");
}

f32 CameraEventTalkAI::m45() {
    return *_68;
}

bool CameraEventTalkAI::m46() {
    return *_70;
}

bool CameraEventTalkAI::m48() {
    return *_78;
}

}  // namespace uking::ai
