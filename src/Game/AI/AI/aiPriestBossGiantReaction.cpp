#include "Game/AI/AI/aiPriestBossGiantReaction.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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

void PriestBossGiantReaction::calc_() {
    EnemyDefaultReaction::calc_();

    if (!_90) {
        auto* manager = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr());
        if (manager) {
            const s32 damage = manager->getDamage();
            if (damage >= 1 && manager->checkDamageFlags(22))
                _90 = true;
        }
    }

    if (_90 && *mPriestBossUrbosasFuryEShock_a) {
        if (!_70.sub_7101241B6C())
            xlinkSearchAndEmit(mActor, "ElectricShock", 2, &_70);
    } else if (_70.sub_7101241B6C()) {
        _70.fadeXLink();
    }
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
