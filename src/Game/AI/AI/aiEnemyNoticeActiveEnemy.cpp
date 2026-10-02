#include "Game/AI/AI/aiEnemyNoticeActiveEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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
    sub_71003A4B3C();
}

void EnemyNoticeActiveEnemy::leave_() {
    sub_71005DB3EC(mActor);
}

void EnemyNoticeActiveEnemy::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void EnemyNoticeActiveEnemy::sub_71003A4B3C() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
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
        ksys::act::acquireActor(mTargetActor_d, &acc);
        sead::Vector3f pos;
        acc.getActorMtx().getTranslation(pos);
        sub_71005DB1D8(mActor, pos);
    } else {
        sub_71005DB3EC(mActor);
    }
}

}  // namespace uking::ai
