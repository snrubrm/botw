#include "Game/AI/Action/actionRegistedActorSetActionBase.h"

namespace uking::action {

RegistedActorSetActionBase::RegistedActorSetActionBase(const InitArg& arg) : ksys::act::ai::Action(arg), _20(mActor) {}

RegistedActorSetActionBase::~RegistedActorSetActionBase() = default;

bool RegistedActorSetActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RegistedActorSetActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _20.sub_71006F0354(*mTeachSelfRegistedActor_s);
}

void RegistedActorSetActionBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void RegistedActorSetActionBase::loadParams_() {
    getStaticParam(&mTeachSelfRegistedActor_s, "TeachSelfRegistedActor");
}

void RegistedActorSetActionBase::calc_() {
    _20.sub_71006F03D0();
}

bool RegistedActorSetActionBase::handleMessage_(const ksys::Message* message) {
    return _20.sub_71006F0448(*message);
}

bool RegistedActorSetActionBase::handleAck_(const ksys::MessageAck* ack) {
    return _20.sub_71006F0604(*ack);
}

}  // namespace uking::action
