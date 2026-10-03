#include "Game/AI/AI/aiEnemyChemTargetAction.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyChemTargetAction::EnemyChemTargetAction(const InitArg& arg) : EnemyChemTargetActionBase(arg) {}

EnemyChemTargetAction::~EnemyChemTargetAction() = default;

bool EnemyChemTargetAction::init_(sead::Heap* heap) {
    return EnemyChemTargetActionBase::init_(heap);
}

void EnemyChemTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyChemTargetActionBase::enter_(params);
}

bool EnemyChemTargetAction::m35() {
    if (EnemyChemTargetActionBase::m35())
        return true;

    sead::Matrix34f mtx;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.sub_7100D11188(&mtx);
    const sead::Vector2f pos(mtx.m[0][3], mtx.m[2][3]);
    const sead::Vector2f actor_pos(mActor->getMtx().m[0][3], mActor->getMtx().m[2][3]);
    const f32 dist = (pos - actor_pos).length();
    return dist < accessor.sub_7100D11254() + *mActionDist_s +
                      sub_71007320F0(mActor, *mWeaponIdx_s);
}

void EnemyChemTargetAction::calc_() {
    EnemyChemTargetActionBase::calc_();
}

void EnemyChemTargetAction::leave_() {
    EnemyChemTargetActionBase::leave_();
}

void EnemyChemTargetAction::loadParams_() {
    EnemyChemTargetActionBase::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void EnemyChemTargetAction::m36(ksys::act::ai::InlineParamPack* params) {
    params->addActor(*mTargetActor_d, "TargetActor", -1);
}

}  // namespace uking::ai
