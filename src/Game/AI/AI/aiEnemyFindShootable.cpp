#include "Game/AI/AI/aiEnemyFindShootable.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyFindShootable::EnemyFindShootable(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyFindShootable::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: frame layout only (the original has the ActorConstDataAccess below the param pack)
void EnemyFindShootable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    acc.getActorMtx().getTranslation(_68);
    _74 = acc.sub_7100D10E6C(30);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_68, "TargetPos", -1);
    changeChild("接近", &pack);
}

void EnemyFindShootable::leave_() {
    if (mActor->getConnectedCalcChild())
        mActor->resetConnectedCalcChild(false);
    sub_71005DB3EC(mActor);
}

void EnemyFindShootable::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getStaticParam(&mAttOffset_s, "AttOffset");
    getStaticParam(&mCanGrabHeavy_s, "CanGrabHeavy");
    getStaticParam(&mGrabCheckRadius_s, "GrabCheckRadius");
    getStaticParam(&mChaseItemDist_s, "ChaseItemDist");
    getStaticParam(&mChaseItemSpeed_s, "ChaseItemSpeed");
}

}  // namespace uking::ai
