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

void CameraEventTalkAIRet::m49() {
    _80 = *_70;
    if (!act::sub_710079BE9C(_80))
        _80 = 0;
}

void CameraEventTalkAIRet::m50() {
    auto* camera = getCamera();
    if (!camera)
        return;

    camera->_860._39c = camera->_860._72c._40;
    camera->_860._3cc = camera->_860._72c._70;
    camera->_860._3d8 = camera->_860._72c._7c;
}

void CameraEventTalkAIRet::m52(ksys::act::ai::InlineParamPack* params) {
    params->addBool(_62 == 1, "Return", -1);
}

}  // namespace uking::ai
