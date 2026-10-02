#include "Game/AI/AI/aiEnemyChemTargetActionBase.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

EnemyChemTargetActionBase::EnemyChemTargetActionBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool EnemyChemTargetActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyChemTargetActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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

void EnemyChemTargetActionBase::m36() {}

}  // namespace uking::ai
