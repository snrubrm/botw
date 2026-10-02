#include "Game/AI/AI/aiCameraEventTalkAI.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

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

// NON_MATCHING: instruction scheduling in the inlined matrix multiplication (zero vector materialised earlier)
void CameraEventTalkAI::m50() {
    auto* camera = getCamera();
    if (!camera)
        return;

    ksys::act::ActorConstDataAccess accessor;
    sub_7100924BE4(&accessor);
    if (!accessor.hasProc())
        return;

    const auto& mtx = accessor.getActorMtx();
    auto& state = camera->_860;
    state._39c.makeR({0, sead::Mathf::pi(), 0});
    state._39c.setMul(mtx, state._39c);

    sead::Vector3f dir;
    mtx.getBase(dir, 2);
    sead::Vector3f pos;
    mtx.getTranslation(pos);
    const f32 len = dir.length();
    if (len > 0)
        dir *= 5.0f / len;
    pos += dir;
    state._39c.setTranslation(pos);
    state._3cc = pos;
    state._3cc.y += 2.5f;
    state._3d8 = pos;
    state._3d8.y += 1.5f;
}

}  // namespace uking::ai
