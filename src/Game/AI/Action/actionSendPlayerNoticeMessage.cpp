#include "Game/AI/Action/actionSendPlayerNoticeMessage.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

SendPlayerNoticeMessage::SendPlayerNoticeMessage(const InitArg& arg)
    : SendPlayerNoticeMessageBase(arg) {}

SendPlayerNoticeMessage::~SendPlayerNoticeMessage() = default;

bool SendPlayerNoticeMessage::init_(sead::Heap* heap) {
    return SendPlayerNoticeMessageBase::init_(heap);
}

void SendPlayerNoticeMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    SendPlayerNoticeMessageBase::enter_(params);
}

void SendPlayerNoticeMessage::leave_() {
    SendPlayerNoticeMessageBase::leave_();
}

void SendPlayerNoticeMessage::loadParams_() {
    SendPlayerNoticeMessageBase::loadParams_();
}

void SendPlayerNoticeMessage::calc_() {
    SendPlayerNoticeMessageBase::calc_();
}

void SendPlayerNoticeMessage::m32() {
    ksys::act::ActorConstDataAccess accessor;
    auto& link = ksys::act::PlayerInfo::getSomeProcLink();
    ksys::act::acquireActor(&link, &accessor);
    const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
    auto* actor = mActor;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
        auto& data = _58._18.mData;
        data._0 = link;
        data._10.acquire(actor, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = pos;
        data._34 = 0;
    }
}

}  // namespace uking::action
