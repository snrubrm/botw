#include "Game/AI/AI/aiEnemyChemTargetActionBase.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyChemTargetActionBase::EnemyChemTargetActionBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyChemTargetActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyChemTargetActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (m35()) {
        if (m34()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            m36(&pack);
            changeChild("アクション", &pack);
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("回転", &pack);
        }
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("移動", &pack);
    }
}

void EnemyChemTargetActionBase::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("アクション")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        } else if (isCurrentChild("回転")) {
            if (m35()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(*mTargetPos_d, "TargetPos", -1);
                m36(&pack);
                changeChild("アクション", &pack);
            } else {
                setFailed();
            }
        } else if (m34()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            m36(&pack);
            changeChild("アクション", &pack);
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("回転", &pack);
        }
        return;
    }

    if (child->isChangeable() && !isCurrentChild("アクション") && m35()) {
        if (m34()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            m36(&pack);
            changeChild("アクション", &pack);
            return;
        }
        if (!isCurrentChild("回転")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("回転", &pack);
            return;
        }
    }
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void EnemyChemTargetActionBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyChemTargetActionBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mActionDist_s, "ActionDist");
    getStaticParam(&mActionDir_s, "ActionDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool EnemyChemTargetActionBase::m34() {
    sead::Vector3f dir = *mTargetPos_d;
    dir -= mActor->getMtx().getTranslation();
    dir.normalize();
    const auto& mtx = mActor->getMtx();
    const sead::Vector3f front = {mtx(0, 2), mtx(1, 2), mtx(2, 2)};
    return dir.dot(front) >= sead::Mathf::cos(*mActionDir_s);
}

bool EnemyChemTargetActionBase::m35() {
    sead::Vector3f diff = *mTargetPos_d;
    diff -= mActor->getMtx().getTranslation();
    const f32 dist = diff.length();
    return dist < *mActionDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
}

void EnemyChemTargetActionBase::m36(ksys::act::ai::InlineParamPack* params) {}

}  // namespace uking::ai
