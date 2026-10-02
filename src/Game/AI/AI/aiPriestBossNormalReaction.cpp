#include "Game/AI/AI/aiPriestBossNormalReaction.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossNormalReaction::PriestBossNormalReaction(const InitArg& arg)
    : EnemyDefaultReaction(arg), _a8() {}

PriestBossNormalReaction::~PriestBossNormalReaction() = default;

bool PriestBossNormalReaction::init_(sead::Heap* heap) {
    return EnemyDefaultReaction::init_(heap);
}

void PriestBossNormalReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyDefaultReaction::enter_(params);
    if (auto* mgr = mActor->getDamageMgr())
        mgr->addDamageCallback(0, &_80);
    _c9 = false;
    *mPriestBossUrbosasFuryEShock_a = false;
}

void PriestBossNormalReaction::leave_() {
    EnemyDefaultReaction::leave_();
    if (_a8.sub_7101241B6C())
        _a8.fadeXLink();
    if (auto* mgr = mActor->getDamageMgr())
        mgr->removeDamageCallback(&_80);
}

void PriestBossNormalReaction::loadParams_() {
    EnemyDefaultReaction::loadParams_();
    getStaticParam(&mIsUseQuickRecover_s, "IsUseQuickRecover");
    getAITreeVariable(&mPriestBossUrbosasFuryEShock_a, "PriestBossUrbosasFuryEShock");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

bool PriestBossNormalReaction::m34(dmg::DamageManagerBase* damage_mgr, int damage_type) {
    return false;
}

void PriestBossNormalReaction::m35(dmg::DamageManagerBase* damage_mgr, int damage_type, bool x,
                                   ksys::act::ai::InlineParamPack* params) {
    if (damage_mgr->checkDamageFlags(22)) {
        _c8 = true;
        changeChild("ウルボザの怒り", params);
        return;
    }
    _c8 = false;
    EnemyDefaultReaction::m35(damage_mgr, damage_type, x, params);
}

bool PriestBossNormalReaction::m45() {
    return false;
}

}  // namespace uking::ai
