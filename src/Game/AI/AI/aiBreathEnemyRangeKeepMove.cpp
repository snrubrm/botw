#include "Game/AI/AI/aiBreathEnemyRangeKeepMove.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

BreathEnemyRangeKeepMove::BreathEnemyRangeKeepMove(const InitArg& arg) : EnemyRangeKeepMove(arg) {}

BreathEnemyRangeKeepMove::~BreathEnemyRangeKeepMove() = default;

bool BreathEnemyRangeKeepMove::init_(sead::Heap* heap) {
    if (!EnemyRangeKeepMove::init_(heap))
        return false;
    return sub_710033FB98(heap);
}

void BreathEnemyRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRangeKeepMove::enter_(params);
    _16c = false;
    _160 = ksys::Timer(0, 0);
    changeChild("ブレス開始");
}

void BreathEnemyRangeKeepMove::leave_() {
    EnemyRangeKeepMove::leave_();
    sub_7100340570();
}

void BreathEnemyRangeKeepMove::loadParams_() {
    EnemyRangeKeepMove::loadParams_();
    getStaticParam(&mEnlargeTime_s, "EnlargeTime");
    getStaticParam(&mAttackRatio_s, "AttackRatio");
    getStaticParam(&mBreathSize_s, "BreathSize");
    getStaticParam(&mBreathName_s, "BreathName");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mLoopTime_s, "LoopTime");
    getStaticParam(&mBreathEndDist_s, "BreathEndDist");
    getStaticParam(&mBreathMinTime_s, "BreathMinTime");
}

void BreathEnemyRangeKeepMove::sub_7100340570() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        auto& link = enemy->getActorPartsActor(mBreathName_s.cstr());
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(&link, &acc);
        acc.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

}  // namespace uking::ai
