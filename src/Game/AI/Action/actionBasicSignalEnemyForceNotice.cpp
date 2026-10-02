#include "Game/AI/Action/actionBasicSignalEnemyForceNotice.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

BasicSignalEnemyForceNotice::BasicSignalEnemyForceNotice(const InitArg& arg)
    : BasicSignalEnemy(arg) {}

BasicSignalEnemyForceNotice::~BasicSignalEnemyForceNotice() = default;

bool BasicSignalEnemyForceNotice::init_(sead::Heap* heap) {
    return BasicSignalEnemy::init_(heap);
}

void BasicSignalEnemyForceNotice::enter_(ksys::act::ai::InlineParamPack* params) {
    BasicSignalEnemy::enter_(params);
    _80 = 0;
}

void BasicSignalEnemyForceNotice::leave_() {
    BasicSignalEnemy::leave_();
}

void BasicSignalEnemyForceNotice::loadParams_() {
    BasicSignalEnemy::loadParams_();
    getStaticParam(&mInterval_s, "Interval");
}

void BasicSignalEnemyForceNotice::calc_() {
    BasicSignalEnemy::calc_();
}

void BasicSignalEnemyForceNotice::sub_71000BA308() {
    auto& link = ksys::act::PlayerInfo::getSomeProcLink();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
    auto* actor = mActor;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_28._18.mLock);
        auto& data = _28._18.mData;
        data._0 = link;
        data._10.acquire(actor, false);
        data._20 = 0;
        data._24 = 2;
        data._28 = pos;
        data._34 = 2;
    }
    sub_71005E1630(mActor, &_28, nullptr);
}

void BasicSignalEnemyForceNotice::m32() {
    sub_71000BA308();
    _80 = *mInterval_s;
}

void BasicSignalEnemyForceNotice::m34() {
    if (_80 <= 0.0f) {
        sub_71000BA308();
        _80 = *mInterval_s;
        return;
    }
    ksys::Timer::update(&_80, -1.0f);
}

}  // namespace uking::action
