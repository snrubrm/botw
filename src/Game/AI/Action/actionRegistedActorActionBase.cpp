#include "Game/AI/Action/actionRegistedActorActionBase.h"

namespace uking::action {

RegistedActorActionBase::RegistedActorActionBase(const InitArg& arg) : ksys::act::ai::Action(arg), _20(mActor) {}

RegistedActorActionBase::~RegistedActorActionBase() = default;

bool RegistedActorActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RegistedActorActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _20.sub_71006F0354(*mTeachSelfRegistedActor_s);
}

void RegistedActorActionBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void RegistedActorActionBase::loadParams_() {
    getStaticParam(&mTeachSelfRegistedActor_s, "TeachSelfRegistedActor");
}

void RegistedActorActionBase::calc_() {
    _20.sub_71006F03D0();
}

bool RegistedActorActionBase::handleMessage_(const ksys::Message* message) {
    return _20.sub_71006F0448(*message);
}

bool RegistedActorActionBase::handleAck_(const ksys::MessageAck* ack) {
    return _20.sub_71006F0604(*ack);
}

}  // namespace uking::action
