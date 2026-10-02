#include "Game/AI/AI/aiSandwormAttackMove.h"
#include <math/seadVector.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SandwormAttackMove::SandwormAttackMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormAttackMove::~SandwormAttackMove() = default;

bool SandwormAttackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: scheduling of the two address computations for search()
void SandwormAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _70._30.search(_70._28, mDamageBaseNode_s);
    _70._68 = *mDamageAngle_s;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("攻撃移動", &pack);
}

void SandwormAttackMove::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("攻撃移動")) {
            sub_71005DA114(mActor, &_70);
            if (sub_710072E368(mActor))
                sub_71005570C4();
            else
                setFinished();
            return;
        }
        setFinished();
    } else if (child->isChangeable()) {
        if (isCurrentChild("離脱")) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
            if (diff.length() > *mSecessionDist_s || !sub_710072E368(mActor))
                setFinished();
        } else if (isCurrentChild("攻撃移動")) {
            const sead::Vector3f pos = mActor->getMtx().getTranslation();
            const sead::Vector2f diff(pos.x - mTargetPos_d->x, pos.z - mTargetPos_d->z);
            if (diff.length() > *mLostDist_s)
                setFailed();
        }
    }

    if (isCurrentChild("攻撃移動"))
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void SandwormAttackMove::leave_() {
    sub_71005DA114(mActor, &_70);
}

void SandwormAttackMove::loadParams_() {
    getStaticParam(&mSecessionDist_s, "SecessionDist");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mDamageAngle_s, "DamageAngle");
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mDamageBaseNode_s, "DamageBaseNode");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: operand order of the three fmul (v * t in the original)
void SandwormAttackMove::sub_71005570C4() {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f pos;
    mtx.getBase(pos, 2);
    pos = pos * *mSecessionDist_s + mtx.getTranslation();
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("離脱", &pack);
}

}  // namespace uking::ai
