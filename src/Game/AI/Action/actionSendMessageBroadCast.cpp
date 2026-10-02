#include "Game/AI/Action/actionSendMessageBroadCast.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

SendMessageBroadCast::SendMessageBroadCast(const InitArg& arg) : SendMessage(arg) {}

SendMessageBroadCast::~SendMessageBroadCast() = default;

bool SendMessageBroadCast::init_(sead::Heap* heap) {
    return SendMessage::init_(heap);
}

void SendMessageBroadCast::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_40._18.mLock);
        _40._18.mLink.acquire(actor, false);
    }
    sub_71005E02E0(actor, &_40, &_30);
    SendMessage::enter_(params);
}

void SendMessageBroadCast::leave_() {
    SendMessage::leave_();
}

void SendMessageBroadCast::loadParams_() {
    SendMessage::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

void SendMessageBroadCast::calc_() {
    SendMessage::calc_();
    if (*mSendTiming_s == 1) {
        auto* actor = mActor;
        if (!_30.hasProc())
            sub_71005E02E0(actor, &_40, &_30);
    }
}

// NON_MATCHING: stack slot of the MessageType temporaries (x29-0x14 vs x29-0x18; see OctarockEscape)
void SendMessageBroadCast::doSendMessage() {
    auto* actor = mActor;
    switch (*mMsgType_s) {
    case 0:
        if (_30.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_30, &accessor);
            if (accessor.hasProc())
                actor->sendMessage(*accessor.getMessageTransceiverId(), 0x8000004, nullptr, true);
        }
        break;
    case 2:
        if (_30.hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&_30, &accessor);
            if (accessor.hasProc())
                actor->sendMessage(*accessor.getMessageTransceiverId(), 0x8000046, nullptr, true);
        }
        break;
    }
}

}  // namespace uking::action
