#include "Game/AI/Action/actionSwitchWindmill.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

SwitchWindmill::SwitchWindmill(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwitchWindmill::~SwitchWindmill() = default;

bool SwitchWindmill::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchWindmill::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwitchWindmill::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchWindmill::loadParams_() {
    getStaticParam(&mSwRadTh_s, "SwRadTh");
    getStaticParam(&mSwRadAllowance_s, "SwRadAllowance");
    getStaticParam(&mRotAccel_s, "RotAccel");
    getStaticParam(&mMaxRotSpeed_s, "MaxRotSpeed");
    getStaticParam(&mTargetNodeName_s, "TargetNodeName");
}

void SwitchWindmill::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SwitchWindmill::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003)
        mActor->emitBasicSigOff();
    return false;
}

}  // namespace uking::action
