#include "Game/Actor/Action/actionSendNoticeMessageBase.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

SendNoticeMessageBase::SendNoticeMessageBase(const InitArg& arg)
    : OnetimeStopASPlay(arg) {}

SendNoticeMessageBase::~SendNoticeMessageBase() = default;

bool SendNoticeMessageBase::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void SendNoticeMessageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    m32();
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, mTargetActorName_s);
    _58.sub_710070DD78(accessor, true);
}

void SendNoticeMessageBase::leave_() {
    OnetimeStopASPlay::leave_();
}

void SendNoticeMessageBase::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mTargetActorName_s, "TargetActorName");
}

void SendNoticeMessageBase::calc_() {
    OnetimeStopASPlay::calc_();
}

void SendNoticeMessageBase::m32() {
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
