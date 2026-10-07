#include "Game/AI/AI/aiBackAttackEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

BackAttackEnemyBattle::BackAttackEnemyBattle(const InitArg& arg) : EnemyBattle(arg) {}

BackAttackEnemyBattle::~BackAttackEnemyBattle() = default;

bool BackAttackEnemyBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void BackAttackEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sead::DynamicCast<act::Enemy>(mActor)) {
        setFailed();
        return;
    }

    if (sub_7100325F84()) {
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        changeToBackAttack();
    } else {
        EnemyBattle::enter_(params);
    }
}

void BackAttackEnemyBattle::leave_() {
    EnemyBattle::leave_();
}

void BackAttackEnemyBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mBackAttackAngle_s, "BackAttackAngle");
}

void BackAttackEnemyBattle::calc_() {
    if (!isCurrentChild("背面攻撃")) {
        EnemyBattle::calc_();
        return;
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
        return;
    }

    sub_71005DA114(mActor, &_98);
    if (child->isFailed()) {
        setFailed();
    } else {
        sub_7100381ED4();
        m37();
    }
}

void BackAttackEnemyBattle::changeToBackAttack() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("背面攻撃", &pack);
    setDamageCallbackTiming(mActor, 4, &_98);
}

// NON_MATCHING: the target Z load and first subtraction are scheduled in a different order.
bool BackAttackEnemyBattle::sub_7100325F84() {
    using ksys::act::ai::RootAiFlag2;
    if (testRootAiFlag2(RootAiFlag2::_1) || testRootAiFlag2(RootAiFlag2::_0) ||
        testRootAiFlag2(RootAiFlag2::_4) || !sub_7100326384())
        return false;
    auto* actor = mActor;
    const auto& position = actor->getMtx().getTranslation();
    const auto& target = sub_71005D9330(actor);
    sead::Vector3f direction(target.x - position.x, 0.0f, target.z - position.z);
    direction.normalize();
    const auto& velocity = sub_71005D9548(actor);
    sead::Vector3f movement(velocity.x, 0.0f, velocity.z);
    if (movement.normalize() < 0.1f)
        return false;
    return direction.dot(movement) >= 0.8660254f;
}

// NON_MATCHING: the gravity and up vectors occupy separate stack slots.
bool BackAttackEnemyBattle::sub_7100326384() {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    const auto up = getUpDir(gravity);
    const auto& matrix = sub_71005D96A8(mActor);
    auto forward = matrix.getBase(2);
    ksys::util::sub_71011EFA00(&forward, forward, up);
    forward.normalize();
    auto displacement = matrix.getTranslation() - mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&displacement, displacement, up);
    displacement.normalize();
    return forward.dot(displacement) >= sead::Mathf::cos(*mBackAttackAngle_s);
}

}  // namespace uking::ai
