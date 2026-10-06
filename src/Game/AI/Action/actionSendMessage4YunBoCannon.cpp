#include "Game/AI/Action/actionSendMessage4YunBoCannon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

SendMessage4YunBoCannon::SendMessage4YunBoCannon(const InitArg& arg) : SendMessage(arg) {}

SendMessage4YunBoCannon::~SendMessage4YunBoCannon() = default;

bool SendMessage4YunBoCannon::init_(sead::Heap* heap) {
    return SendMessage::init_(heap);
}

void SendMessage4YunBoCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    SendMessage::enter_(params);
}

void SendMessage4YunBoCannon::leave_() {
    SendMessage::leave_();
}

void SendMessage4YunBoCannon::loadParams_() {
    SendMessage::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

void SendMessage4YunBoCannon::calc_() {
    SendMessage::calc_();
}

void SendMessage4YunBoCannon::doSendMessage() {
    auto* actor = mActor;
    ksys::act::ActorConstDataAccess accessor;
    switch (*mMsgType_s) {
    case 0:
        if (actor->getCreateArgBaseProcLink().hasProc()) {
            ksys::act::acquireActor(&actor->getCreateArgBaseProcLink(), &accessor);
            actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000067),
                               nullptr, true);
        }
        break;
    case 1:
        if (actor->getCreateArgBaseProcLink().hasProc()) {
            ksys::act::acquireActor(&actor->getCreateArgBaseProcLink(), &accessor);
            actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000066),
                               nullptr, true);
        }
        break;
    case 2:
        if (actor->getCreateArgBaseProcLink().hasProc()) {
            ksys::act::acquireActor(&actor->getCreateArgBaseProcLink(), &accessor);
            actor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000068),
                               nullptr, true);
        }
        break;
    }
}

}  // namespace uking::action
