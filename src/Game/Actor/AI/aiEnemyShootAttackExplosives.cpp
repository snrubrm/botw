#include "Game/Actor/AI/aiEnemyShootAttackExplosives.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ai {

EnemyShootAttackExplosives::EnemyShootAttackExplosives(const InitArg& arg)
    : EnemyBaseArrowAttack(arg) {}

EnemyShootAttackExplosives::~EnemyShootAttackExplosives() = default;

void EnemyShootAttackExplosives::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sub_71005DA9A8(mActor, *mWeaponIdx_s)) {
        EnemyBaseArrowAttack::enter_(params);
        return;
    }
    if (mActor) {
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        if (sead::Vector2f(position.x - mTargetPos_d->x,
                           position.z - mTargetPos_d->z).length() >= *mExplosivesAvoidDist_s) {
            m35();
            return;
        }
        if (canBackstep()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("後ずさり", &pack);
            return;
        }
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("逃走", &pack);
}

// NON_MATCHING: SafeString temporaries and target-direction loads use different placement.
void EnemyShootAttackExplosives::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        EnemyBaseArrowAttack::calc_();
        return;
    }
    if (isCurrentChild("リロード") || isCurrentChild("後ずさり")) {
        if (mActor) {
            const sead::Vector3f position = mActor->getMtx().getTranslation();
            if (sead::Vector2f(position.x - mTargetPos_d->x,
                               position.z - mTargetPos_d->z).length() >= *mExplosivesAvoidDist_s) {
                m35();
                return;
            }
            if (canBackstep()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                changeChild("後ずさり", &pack);
                return;
            }
        }
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("逃走", &pack);
    } else if (isCurrentChild("逃走")) {
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        sead::Vector3f direction = *mTargetPos_d - position;
        direction.y = 0.0f;
        direction.normalize();
        if (direction.dot(mActor->getMtx().getBase(2)) <= sead::Mathf::cos(*mTurnStartAng_s)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("回転", &pack);
        } else {
            changeToPrepare();
        }
    } else if (isCurrentChild("回転")) {
        changeToPrepare();
    } else {
        EnemyBaseArrowAttack::calc_();
    }
}

void EnemyShootAttackExplosives::loadParams_() {
    EnemyBaseArrowAttack::loadParams_();
    getStaticParam(&mExplosivesAvoidDist_s, "ExplosivesAvoidDist");
    getStaticParam(&mTurnStartAng_s, "TurnStartAng");
}

}  // namespace uking::ai
