#include "Game/AI/AI/aiEnemyChaseTargetAndAction.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyChaseTargetAndAction::EnemyChaseTargetAndAction(const InitArg& arg)
    : UnarmedEnemySearch(arg) {}

EnemyChaseTargetAndAction::~EnemyChaseTargetAndAction() = default;

void EnemyChaseTargetAndAction::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
    m37();
}

// NON_MATCHING: register allocation only (ours keeps &accessor in a callee-saved register across the
// acquire call, the original re-materialises it)
void EnemyChaseTargetAndAction::calc_() {
    UnarmedEnemySearch::calc_();
    if (isGoStraightOrMove()) {
        sead::Vector3f pos;
        ksys::act::ActorConstDataAccess accessor;
        if (mTargetActor_d->hasProc()) {
            ksys::act::acquireActor(mTargetActor_d, &accessor);
            accessor.getActorMtx().getTranslation(pos);
        } else {
            pos = sub_71005D9330(mActor);
        }
        sub_71005DB068(mActor, pos);
    } else {
        sub_71005DB3EC(mActor);
    }
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("アクション")) {
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                setFailed();
        }
    }
}

bool EnemyChaseTargetAndAction::sub_7100384D50() {
    if (sub_71005DEC08(mTargetActor_d, mActor, *mLostDist_s, *mLostSpeed_s, *mLostAng_s))
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    const auto& target_pos = accessor.getActorMtx().getTranslation();
    const auto& pos = mActor->getMtx().getTranslation();
    if ((target_pos - pos).length() <= getReachDistanceMaybe())
        return true;
    return sub_7100739030(mActor, *mTargetActor_d);
}

// NON_MATCHING: list initialization and target-coordinate loads are scheduled differently.
void EnemyChaseTargetAndAction::m37() {
    if (sub_71005DEC08(mTargetActor_d, mActor, *mLostDist_s, *mLostSpeed_s, *mLostAng_s))
        setFailed();
    _90.reset(*mRepathTime_s);
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    const auto& target = accessor.getActorMtx().getTranslation();
    if (!sub_710072E154(mActor, target, nullptr, -1)) {
        if (!isGoStraightOrMove())
            changeToLookAround();
        sead::FixedObjList<sead::Vector3f, 8> points;
        points.emplaceBack(target);
        m41(points);
    } else if (!isGoStraight()) {
        startMoveToTargetMaybe(target);
    } else {
        getCurrentChild()->setDynamicParam(target, "TargetPos");
    }
}

void EnemyChaseTargetAndAction::m38() {
    if (sub_71005DEC08(mTargetActor_d, mActor, *mLostDist_s, *mLostSpeed_s, *mLostAng_s)) {
        setFailed();
        return;
    }
    if (sub_7100384D50()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(*mTargetActor_d, "TargetActor", -1);
        changeChild("アクション", &pack);
        return;
    }
    _90.update();
    if (_90.value <= sead::Mathf::epsilon())
        m37();
}

void EnemyChaseTargetAndAction::m39() {
    if (sub_71005DEC08(mTargetActor_d, mActor, *mLostDist_s, *mLostSpeed_s, *mLostAng_s)) {
        setFailed();
        return;
    }
    if (sub_7100384D50()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addActor(*mTargetActor_d, "TargetActor", -1);
        changeChild("アクション", &pack);
        return;
    }
    m37();
}

bool EnemyChaseTargetAndAction::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyChaseTargetAndAction::leave_() {
    UnarmedEnemySearch::leave_();
    sub_71005DB3EC(mActor);
}

void EnemyChaseTargetAndAction::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mLostSpeed_s, "LostSpeed");
    getStaticParam(&mLostAng_s, "LostAng");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
