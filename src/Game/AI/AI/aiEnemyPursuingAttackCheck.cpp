#include "Game/AI/AI/aiEnemyPursuingAttackCheck.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyLevel.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

EnemyPursuingAttackCheck::EnemyPursuingAttackCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyPursuingAttackCheck::~EnemyPursuingAttackCheck() = default;

// NON_MATCHING: only the y term of the final dot product: the original multiplies forward.y by a loaded -0.0f
// constant (`fmul s0, s8, s0`), ours negates the product (`fnmul`); everything else matches
// Whether a pursuing (follow up) attack from behind is possible: the actor is in front of the target direction, the
// target is within `AttackAng` and `PursuingAttackStartAng` of the forward vector.
bool EnemyPursuingAttackCheck::sub_71003A90D8() {
    auto* actor = mActor;
    if (!actor)
        return false;
    const auto* level = actor->getParam()->getRes().mGParamList->getEnemyLevel();
    if (!level || !*level->mIsBackSwiftAttack)
        return false;
    if (!(_58.value <= sead::Mathf::epsilon()))
        return false;
    if (!sub_710072E1B4(actor, false))
        return false;
    if (!sub_710072DDB8(sub_71005D9330(mActor), mActor->getMtx(), *mAttackAng_s))
        return false;

    const sead::Matrix34f& mtx = sub_71005D96A8(actor);
    sead::Vector3f forward;
    mtx.getBase(forward, 2);
    forward.y = 0.0f;
    forward.normalize();
    sead::Vector3f to_target = sub_71005D9330(actor);
    to_target -= actor->getMtx().getTranslation();
    to_target.y = 0.0f;
    to_target.normalize();
    return forward.dot(-to_target) <= sead::Mathf::cos(*mPursuingAttackStartAng_s);
}

void EnemyPursuingAttackCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    _58.reset(0.0f);
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_1) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0) ||
        testRootAiFlag2(ksys::act::ai::RootAiFlag2::_4)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("通常戦闘", &pack);
        return;
    }

    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    if (sub_71003A90D8()) {
        changeToFollowUpAttack();
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
        changeChild("通常戦闘", &pack);
    }
}

// NON_MATCHING: only the SafeString vtable address: the original computes `vtable + 0x10` once (x21) after the
// second isCurrentChild("通常戦闘") and reuses it with a `stp` for the "TargetPos" string; ours re-adds it per string
void EnemyPursuingAttackCheck::calc_() {
    auto* child = getCurrentChild();
    const bool in_follow_up = (child->isFinished() || child->isFailed()) && isCurrentChild("追撃ち攻撃");
    if (in_follow_up) {
        if (getCurrentChild()->isFailed()) {
            setFailed();
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("通常戦闘", &pack);
        }
        return;
    }

    if (getCurrentChild()->isChangeable() && isCurrentChild("通常戦闘") && sub_71003A90D8()) {
        changeToFollowUpAttack();
        return;
    }

    if (isCurrentChild("通常戦闘") && !(_58.value <= sead::Mathf::epsilon()))
        _58.update();
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

bool EnemyPursuingAttackCheck::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyPursuingAttackCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyPursuingAttackCheck::loadParams_() {
    getStaticParam(&mPursuingAttackInterval_s, "PursuingAttackInterval");
    getStaticParam(&mPursuingAttackIntervalRand_s, "PursuingAttackIntervalRand");
    getStaticParam(&mPursuingAttackStartAng_s, "PursuingAttackStartAng");
    getStaticParam(&mAttackAng_s, "AttackAng");
}

bool EnemyPursuingAttackCheck::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("通常戦闘") && getCurrentChild()->isFinished());
}

bool EnemyPursuingAttackCheck::isFailed() const {
    return ActionBase::isFailed() || (isCurrentChild("通常戦闘") && getCurrentChild()->isFailed());
}

void EnemyPursuingAttackCheck::changeToFollowUpAttack() {
    const s32 rand = *mPursuingAttackIntervalRand_s;
    const f32 random_part = rand * -0.5f;
    const f32 interval = *mPursuingAttackInterval_s;
    _58.reset(s32(interval + random_part) + s32(sead::GlobalRandom::instance()->getU32(rand)));

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追撃ち攻撃", &pack);
}

}  // namespace uking::ai
