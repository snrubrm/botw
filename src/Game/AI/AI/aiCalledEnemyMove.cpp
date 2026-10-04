#include "Game/AI/AI/aiCalledEnemyMove.h"
#include "KingSystem/ActorSystem/actActor.h"
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
        changeToApproach();
    else
        setFailed();
}

void CalledEnemyMove::calc_() {
    if (!mTargetActor_d || !mTargetActor_d->hasProc()) {
        setFailed();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("近づき")) {
            if (child->isFinished())
                changeToWait();
            else
                setFailed();
        } else if (isCurrentChild("待機")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        }
    } else if (child->isChangeable()) {
        sead::Vector2f target;
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(mTargetActor_d, &accessor);
            const sead::Matrix34f& mtx = accessor.getActorMtx();
            target.set(mtx(0, 3), mtx(2, 3));
        }
        const sead::Matrix34f& actor_mtx = mActor->getMtx();
        const sead::Vector2f diff(actor_mtx(0, 3) - target.x, actor_mtx(2, 3) - target.y);
        if (diff.length() > *mLostDist_s)
            setFailed();
    }

    if (isCurrentChild("近づき")) {
        sead::Vector3f pos;
        sub_7100341058(&pos);
        child->setDynamicParam(pos, "TargetPos");
    } else if (isCurrentChild("待機")) {
        sead::Vector3f pos;
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(mTargetActor_d, &accessor);
            accessor.getActorMtx().getTranslation(pos);
        }
        child->setDynamicParam(pos, "TargetPos");
    }
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

void CalledEnemyMove::changeToApproach() {
    sead::Vector3f pos;
    sub_7100341058(&pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("近づき", &pack);
}

void CalledEnemyMove::sub_7100341058(sead::Vector3f* out) {
    if (!out)
        return;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.getActorMtx().getTranslation(*out);
    sead::Vector3f dir;
    accessor.getActorMtx().getBase(dir, 2);
    dir.normalize();
    *out += dir * *mWaitDist_s;
}

void CalledEnemyMove::changeToWait() {
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
