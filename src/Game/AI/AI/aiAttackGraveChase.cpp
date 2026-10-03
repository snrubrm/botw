#include "Game/AI/AI/aiAttackGraveChase.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

AttackGraveChase::AttackGraveChase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AttackGraveChase::~AttackGraveChase() = default;

bool AttackGraveChase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// inline-only in the original (enter_ and calc_ twice); name is a guess.
inline void AttackGraveChase::getTargetPos(sead::Vector3f* out) {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    acc.getActorMtx().getTranslation(*out);
}

void AttackGraveChase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    getTargetPos(&pos);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("行動", &pack);
    _60 = 0.0f;
    _64 = false;
}

// NON_MATCHING: register allocation (the original keeps four floats (actor x / y / z and the target's y) in
// callee-saved registers, ours three); everything else matches
void AttackGraveChase::calc_() {
    ksys::Timer::update(&_60, 1.0f);
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (isCurrentChild("行動")) {
            _60 = *mActionTime_s - *mNearTime_s;
            ksys::act::ai::InlineParamPack pack;
            sead::Vector3f pos;
            getTargetPos(&pos);
            pack.addVec3(pos, "TargetPos", -1);
            changeChild("接近後", &pack);
        } else {
            setFinished();
        }
        return;
    }
    if (child->isFailed()) {
        setFailed();
        return;
    }
    if (child->isChangeable() && *mActionTime_s >= 1 && s32(_60) > *mActionTime_s) {
        setFinished();
        return;
    }

    const f32 x = mActor->getMtx().m[0][3];
    const f32 y = mActor->getMtx().m[1][3];
    const f32 z = mActor->getMtx().m[2][3];
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    const auto& target_mtx = acc.getActorMtx();
    const sead::Vector2f diff(target_mtx.m[0][3] - x, target_mtx.m[2][3] - z);
    const f32 target_y = target_mtx.m[1][3];
    if (diff.length() < *mEndNear_s)
        _64 = true;
    if (acc.isBgGroundHit()) {
        _64 = false;
    } else if (_64 && target_y - y > *mEndHeight_s) {
        setFailed();
        return;
    }

    sead::Vector3f pos;
    getTargetPos(&pos);
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
}

void AttackGraveChase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AttackGraveChase::loadParams_() {
    getStaticParam(&mActionTime_s, "ActionTime");
    getStaticParam(&mNearTime_s, "NearTime");
    getStaticParam(&mEndHeight_s, "EndHeight");
    getStaticParam(&mEndNear_s, "EndNear");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
