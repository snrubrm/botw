#include "Game/AI/Action/actionSendMessageToTargetActor.h"
#include "Game/AI/aiUnk_7102357d20.h"

namespace uking::action {

SendMessageToTargetActor::SendMessageToTargetActor(const InitArg& arg) : SendMessage(arg) {}

SendMessageToTargetActor::~SendMessageToTargetActor() = default;

bool SendMessageToTargetActor::init_(sead::Heap* heap) {
    return SendMessage::init_(heap);
}

void SendMessageToTargetActor::enter_(ksys::act::ai::InlineParamPack* params) {
    SendMessage::enter_(params);
}

void SendMessageToTargetActor::leave_() {
    SendMessage::leave_();
}

void SendMessageToTargetActor::loadParams_() {
    SendMessage::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SendMessageToTargetActor::calc_() {
    SendMessage::calc_();
}

void SendMessageToTargetActor::doSendMessage() {
    if (auto* sender = m34()) {
        m33();
        sender->sub_710070DCC0(mTargetActor_d, true);
    }
}

void SendMessageToTargetActor::m33() {}

}  // namespace uking::action
