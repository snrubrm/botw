#include "Game/AI/AI/aiPriestBossShadowClonesReaction.h"

namespace uking::ai {

PriestBossShadowClonesReaction::PriestBossShadowClonesReaction(const InitArg& arg)
    : EnemyDefaultReaction(arg) {}

PriestBossShadowClonesReaction::~PriestBossShadowClonesReaction() = default;

bool PriestBossShadowClonesReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void PriestBossShadowClonesReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
    sub_710052D98C();
}

void PriestBossShadowClonesReaction::calc_() {
    EnemyDefaultReaction::calc_();
}

void PriestBossShadowClonesReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void PriestBossShadowClonesReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
