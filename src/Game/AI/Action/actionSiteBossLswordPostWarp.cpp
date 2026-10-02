#include "Game/AI/Action/actionSiteBossLswordPostWarp.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

SiteBossLswordPostWarp::SiteBossLswordPostWarp(const InitArg& arg) : LastBossPostNormalWarp(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SiteBossLswordPostWarp::~SiteBossLswordPostWarp() {
    ;
}

bool SiteBossLswordPostWarp::init_(sead::Heap* heap) {
    return LastBossPostNormalWarp::init_(heap);
}

void SiteBossLswordPostWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossPostNormalWarp::enter_(params);
}

void SiteBossLswordPostWarp::leave_() {
    LastBossPostNormalWarp::leave_();
}

void SiteBossLswordPostWarp::loadParams_() {
    LastBossPostNormalWarp::loadParams_();
    getStaticParam(&mCancelSleepPartsName_s, "CancelSleepPartsName");
}

void SiteBossLswordPostWarp::calc_() {
    LastBossPostNormalWarp::calc_();
    if (!sub_71005DD780(mActor, 0x3b, nullptr, 0, 0))
        return;

    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (!boss || mCancelSleepPartsName_s.isEmpty() || !checkHpRate(boss, 0.5f))
        return;
    if (*mIsKeepDisableDraw_d || *mIsPartsActorTgOn_d || boss->_1558.isOn(0x80000))
        return;
    if (!boss->_1128.getActorPartsActor(mCancelSleepPartsName_s).hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&boss->_1128.getActorPartsActor(mCancelSleepPartsName_s), &accessor);
    if (accessor.isStateSleep()) {
        accessor.setProperties(boss->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
        if (!mActor->getConnectedCalcChild()) {
            accessor.setThisActorAsChild(mActor, false);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000002),
                                nullptr, true);
        }
    }
}

}  // namespace uking::action
