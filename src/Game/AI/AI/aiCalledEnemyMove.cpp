#include "Game/AI/AI/aiCalledEnemyMove.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

CalledEnemyMove::CalledEnemyMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CalledEnemyMove::~CalledEnemyMove() = default;

bool CalledEnemyMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CalledEnemyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mTargetActor_d && mTargetActor_d->hasProc())
        sub_7100340C04();
    else
        setFailed();
}

void CalledEnemyMove::leave_() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    _50.x(mActor);
    _50.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
}

void CalledEnemyMove::loadParams_() {
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mWaitDist_s, "WaitDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void CalledEnemyMove::sub_7100340F4C() {
    sead::Vector3f pos;
    {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(mTargetActor_d, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
