#include "Game/AI/AI/aiEnemyChemTargetAction.h"
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
