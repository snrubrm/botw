#include "Game/AI/AI/aiPriestBossGiantReaction.h"
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::ai {

PriestBossGiantReaction::PriestBossGiantReaction(const InitArg& arg) : EnemyDefaultReaction(arg) {}

PriestBossGiantReaction::~PriestBossGiantReaction() = default;

bool PriestBossGiantReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void PriestBossGiantReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
    *mPriestBossUrbosasFuryEShock_a = false;
}

void PriestBossGiantReaction::leave_() {
    EnemyDefaultReaction::leave_();
    if (_70.sub_7101241B6C())
        _70.fadeXLink();
}

void PriestBossGiantReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getAITreeVariable(&mPriestBossUrbosasFuryEShock_a, "PriestBossUrbosasFuryEShock");
}

bool PriestBossGiantReaction::m34(dmg::DamageManagerBase* damage_mgr, int damage_type) {
    return false;
}

void PriestBossGiantReaction::m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
                                  ksys::act::ai::InlineParamPack* params) {
    if (damage_mgr->checkDamageFlags(22)) {
        _90 = true;
        changeChild("ウルボザの怒り", params);
        return;
    }
    _90 = false;
    EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
}

}  // namespace uking::ai
