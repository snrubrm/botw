#include "Game/AI/AI/aiEnemyNoticeActiveEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyNoticeActiveEnemy::EnemyNoticeActiveEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeActiveEnemy::~EnemyNoticeActiveEnemy() = default;

bool EnemyNoticeActiveEnemy::init_(sead::Heap* heap) {
    _4c = 15;
    _50 = 30;
    return true;
}

void EnemyNoticeActiveEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = _4c == _50 ? _4c : sead::GlobalRandom::instance()->getS32Range(_4c, _50);
    changeToNotice();
}

void EnemyNoticeActiveEnemy::calc_() {
    if (!isCurrentChild("気づき")) {
        ksys::Timer::update(&_54, -1.0f);
        if (_54 < 0) {
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        }
    }

    m34();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("気づき"))
            changeToAct();
        else if (child->isFinished())
            setFinished();
        else
            setFailed();
    }

    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mParams.mTargetActor_d, &acc);
    acc.getActorMtx();
    f32* delay = &_48;
    if (acc.sub_7100D10E6C(25))
        *delay = _4c == _50 ? _4c : sead::GlobalRandom::instance()->getS32Range(_4c, _50);
    else
        ksys::Timer::update(delay, -1.0f);

    if (child->isChangeable() && *delay <= 0)
        setFailed();
    else
        getCurrentChild()->setDynamicParam(*mParams.mTargetPos_d, "TargetPos");
}

void EnemyNoticeActiveEnemy::changeToAct() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    pack.addActor(*mParams.mTargetActor_d, "TargetActor", -1);
    changeChild("行動", &pack);
}

void EnemyNoticeActiveEnemy::leave_() {
    sub_71005DB3EC(mActor);
}

void EnemyNoticeActiveEnemy::loadParams_() {
    getDynamicParam(&mParams.mTargetActor_d, "TargetActor");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void EnemyNoticeActiveEnemy::changeToNotice() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mParams.mTargetPos_d, "TargetPos", -1);
    pack.addActor(*mParams.mTargetActor_d, "TargetActor", -1);
    changeChild("気づき", &pack);
}

bool EnemyNoticeActiveEnemy::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("行動"))
        return getCurrentChild()->isFinished();
    return false;
}

void EnemyNoticeActiveEnemy::m34() {
    if (isCurrentChild("気づき")) {
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(mParams.mTargetActor_d, &acc);
        sead::Vector3f pos;
        acc.getActorMtx().getTranslation(pos);
        sub_71005DB1D8(mActor, pos);
    } else {
        sub_71005DB3EC(mActor);
    }
}

}  // namespace uking::ai
