#include "Game/Actor/Action/actionSendTargetActorMessageBase.h"
#include "Game/Actor/aiUnk_7102357d20.h"

namespace uking::action {

SendTargetActorMessageBase::SendTargetActorMessageBase(const InitArg& arg) : SendMessage(arg) {}

SendTargetActorMessageBase::~SendTargetActorMessageBase() = default;

bool SendTargetActorMessageBase::init_(sead::Heap* heap) {
    return SendMessage::init_(heap);
}

void SendTargetActorMessageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    SendMessage::enter_(params);
}

void SendTargetActorMessageBase::leave_() {
    SendMessage::leave_();
}

void SendTargetActorMessageBase::loadParams_() {
    SendMessage::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SendTargetActorMessageBase::calc_() {
    SendMessage::calc_();
}

void SendTargetActorMessageBase::doSendMessage() {
    if (auto* sender = m34()) {
        m33();
        sender->sub_710070DCC0(mTargetActor_d, true);
    }
}

void SendTargetActorMessageBase::m33() {}

}  // namespace uking::action
