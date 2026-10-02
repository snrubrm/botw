#include "Game/AI/Action/actionMsg2CameraResetInterpolate.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

Msg2CameraResetInterpolate::Msg2CameraResetInterpolate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

bool Msg2CameraResetInterpolate::oneShot_() {
    act::Camera* camera = nullptr;
    sub_710092DB74(&camera);
    if (!camera)
        return true;
    auto* mgr = ksys::act::BaseProcMgr::instance();
    if (!mgr || !mgr->isAccessingProcSafe(camera, nullptr))
        return true;

    f32* param = nullptr;
    camera->sub_7100795F40(&param);
    if (param) {
        *param = *mInterpolateParam_d;
        sendMessage(*camera->getMesTransceiverId(), ksys::MessageType(0x8800008), param);
    }
    return true;
}

void Msg2CameraResetInterpolate::loadParams_() {
    getDynamicParam_2(&mInterpolateParam_d, "InterpolateParam");
}

}  // namespace uking::action
