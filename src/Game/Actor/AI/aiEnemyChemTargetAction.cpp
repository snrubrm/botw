#include "Game/Actor/AI/aiEnemyChemTargetAction.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyChemTargetAction::EnemyChemTargetAction(const InitArg& arg) : EnemyTargetAction(arg) {}

EnemyChemTargetAction::~EnemyChemTargetAction() = default;

bool EnemyChemTargetAction::init_(sead::Heap* heap) {
    return EnemyTargetAction::init_(heap);
}

void EnemyChemTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyTargetAction::enter_(params);
}

bool EnemyChemTargetAction::m35() {
    if (EnemyTargetAction::m35())
        return true;

    sead::Matrix34f mtx;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(mTargetActor_d, &accessor);
    accessor.sub_7100D11188(&mtx);
    const sead::Vector2f pos(mtx.m[0][3], mtx.m[2][3]);
    const sead::Vector2f actor_pos(mActor->getMtx().m[0][3], mActor->getMtx().m[2][3]);
    const f32 dist = (pos - actor_pos).length();
    return dist < accessor.sub_7100D11254() + *mActionDist_s +
                      sub_71007320F0(mActor, *mWeaponIdx_s);
}

void EnemyChemTargetAction::calc_() {
    EnemyTargetAction::calc_();
}

void EnemyChemTargetAction::leave_() {
    EnemyTargetAction::leave_();
}

void EnemyChemTargetAction::loadParams_() {
    EnemyTargetAction::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void EnemyChemTargetAction::m36(ksys::act::ai::InlineParamPack* params) {
    params->addActor(*mTargetActor_d, "TargetActor", -1);
}

}  // namespace uking::ai
