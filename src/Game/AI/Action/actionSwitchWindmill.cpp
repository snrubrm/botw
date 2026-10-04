#include "Game/AI/Action/actionSwitchWindmill.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

SwitchWindmill::SwitchWindmill(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwitchWindmill::~SwitchWindmill() = default;

bool SwitchWindmill::init_(sead::Heap* heap) {
    _130 = 0;
    _134 = 0;
    return true;
}

void SwitchWindmill::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _58.setName(mTargetNodeName_s);
    if (auto* model = actor->getModel()) {
        actor->boneHandleStuff(&_58, false);
        _20.search(model, mTargetNodeName_s);
    }
}

void SwitchWindmill::leave_() {
    mActor->sub_71011DA868(&_58);
    _20.remove();
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
