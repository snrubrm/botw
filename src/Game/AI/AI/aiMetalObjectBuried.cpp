#include "Game/AI/AI/aiMetalObjectBuried.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

MetalObjectBuried::MetalObjectBuried(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MetalObjectBuried::~MetalObjectBuried() = default;

bool MetalObjectBuried::init_(sead::Heap* heap) {
    _72 = false;
    return true;
}

void MetalObjectBuried::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MetalObjectBuried::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MetalObjectBuried::loadParams_() {
    getStaticParam(&mPullOutSpeed_s, "PullOutSpeed");
    getStaticParam(&mCheckGroundRadiusScale_s, "CheckGroundRadiusScale");
    getStaticParam(&mIsIgnoreResistanceArea_s, "IsIgnoreResistanceArea");
    getStaticParam(&mIsCheckGrabYPosFix_s, "IsCheckGrabYPosFix");
    getStaticParam(&mIsCheckSelfY_s, "IsCheckSelfY");
    getMapUnitParam(&mIsInGround_m, "IsInGround");
    getMapUnitParam(&mEnableRevival_m, "EnableRevival");
}

bool MetalObjectBuried::handleMessage_(const ksys::Message& message) {
    if (message.getType().value != 0x3000007)
        return false;

    auto* actor = mActor;
    if (*mEnableRevival_m)
        actor->becomePreActor(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
    else
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    return true;
}

}  // namespace uking::ai
