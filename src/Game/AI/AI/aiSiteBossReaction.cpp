#include "Game/AI/AI/aiSiteBossReaction.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::ai {

SiteBossReaction::SiteBossReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SiteBossReaction::~SiteBossReaction() {
    ;
}

bool SiteBossReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void SiteBossReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
}

void SiteBossReaction::leave_() {
    EnemyDefaultReaction::leave_();
}

void SiteBossReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsChangeEffectiveDamage_s, "IsChangeEffectiveDamage");
}

bool SiteBossReaction::m36(int damage_type) {
    if (_74++ >= 3) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
            boss->_1558.set(4);
    }
    return false;
}

}  // namespace uking::ai
