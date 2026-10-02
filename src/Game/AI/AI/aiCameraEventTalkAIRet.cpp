#include "Game/AI/AI/aiCameraEventTalkAIRet.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

CameraEventTalkAIRet::CameraEventTalkAIRet(const InitArg& arg) : CameraEventTalk(arg) {}

void CameraEventTalkAIRet::m43() {
    getStaticParam(&_68, "HeightOffset");
    getDynamicParam_2(&_70, "SavePoint");
    getDynamicParam_2(&_78, "Count");
}

f32 CameraEventTalkAIRet::m45() {
    return *_68;
}

f32 CameraEventTalkAIRet::m47() {
    if (_62 == 1)
        return *_78;
    return -1.0f;
}

void CameraEventTalkAIRet::m52(ksys::act::ai::InlineParamPack* params) {
    params->addBool(_62 == 1, "Return", -1);
}

}  // namespace uking::ai
