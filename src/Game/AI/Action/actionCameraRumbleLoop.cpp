#include "Game/AI/Action/actionCameraRumbleLoop.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/System/Vibration.h"

namespace uking::action {

CameraRumbleLoop::CameraRumbleLoop(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void CameraRumbleLoop::enter_(ksys::act::ai::InlineParamPack* params) {
    setFinished();

    auto* actor = mActor;
    if (!actor)
        return;

    if (*mCamVibId_a != -1) {
        const s32 id = *mCamVibId_a;
        *mCamVibId_a = -1;
        if (auto* vibration = ksys::Vibration::instance())
            vibration->sub_71010BB810(id);
    }

    if (auto* vibration = ksys::Vibration::instance()) {
        const ksys::Vibration::Unk2 request(
            *mPattern_d, sead::Vector3f::zero, 5, &actor->getMessageTransceiver(), *mPower_d, 100.0f,
            *mSideways_d ? sead::Vector3f::ex : sead::Vector3f::ey, 1);
        vibration->sub_71010BB800(request);
    }
}

void CameraRumbleLoop::loadParams_() {
    getDynamicParam_2(&mPattern_d, "Pattern");
    getDynamicParam_2(&mPower_d, "Power");
    getDynamicParam_2(&mSideways_d, "Sideways");
    getAITreeVariable(&mCamVibId_a, "CamVibId");
}

// NON_MATCHING: the original null-checks &message (cbz) before getType()
bool CameraRumbleLoop::handleMessage_(const ksys::Message& message) {
    if (message.getType() != ksys::MessageType(0x2000001))
        return false;
    if (const auto* id = static_cast<const s32*>(message.getUserData()))
        *mCamVibId_a = *id;
    return true;
}

void CameraRumbleLoop::onPreDelete() {
    if (*mCamVibId_a != -1) {
        const s32 id = *mCamVibId_a;
        *mCamVibId_a = -1;
        if (auto* vibration = ksys::Vibration::instance())
            vibration->sub_71010BB810(id);
    }
}

bool CameraRumbleLoop::hasPreDeleteCb() {
    return true;
}

}  // namespace uking::action
