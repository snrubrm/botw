#include "Game/AI/Action/actionSendPlayerNoticeMessageBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

SendPlayerNoticeMessageBase::SendPlayerNoticeMessageBase(const InitArg& arg)
    : OnetimeStopASPlay(arg) {}

SendPlayerNoticeMessageBase::~SendPlayerNoticeMessageBase() = default;

bool SendPlayerNoticeMessageBase::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void SendPlayerNoticeMessageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    m32();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, mTargetActorName_s);
    _58.sub_710070DD78(accessor, true);
}

void SendPlayerNoticeMessageBase::leave_() {
    OnetimeStopASPlay::leave_();
}

void SendPlayerNoticeMessageBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mTargetActorName_s, "TargetActorName");
}

void SendPlayerNoticeMessageBase::calc_() {
    OnetimeStopASPlay::calc_();
}

void SendPlayerNoticeMessageBase::m32() {
    auto* target = sub_71005D9050(mActor);
    auto* actor = mActor;
    const sead::Vector3f& pos = sub_71005D9330(actor);
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_58._18.mLock);
        auto& data = _58._18.mData;
        if (target)
            data._0 = *target;
        else
            data._0.reset();
        data._10.acquire(actor, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = pos;
        data._34 = 0;
    }
}

}  // namespace uking::action
