#include "Game/AI/AI/aiPriestBossShadowClonesReaction.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

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

void PriestBossShadowClonesReaction::sub_710052D98C() {
    _70 = false;

    auto* unit = sead::DynamicCast<Unk_7102450fa8>(*mPriestBossMetaAIUnit_a);
    if (!unit || !unit->isFlagOn(Unk_7102450fa8::Flag::_0))
        return;
    if (unit->sub_7100719FE4(unit->sub_7100719534(mActor)) != 4)
        return;
    if (!isCurrentChild("ショック") && !isCurrentChild("超ショック"))
        return;

    auto* damage_mgr = sub_710072BA90(mActor);
    if (!damage_mgr)
        return;
    if (damage_mgr->getField54() != 7 && damage_mgr->getField54() != 8)
        return;
    if (!ksys::act::isPlayerProfile(damage_mgr->getAttacker()))
        return;

    _70 = unit->isFlagOn(Unk_7102450fa8::Flag::_15);
}

bool PriestBossShadowClonesReaction::m34(dmg::DamageManagerBase* damage_mgr, int damage_type) {
    if (!EnemyDefaultReaction::m34(damage_mgr, damage_type))
        return false;
    sub_710052D98C();
    return true;
}

}  // namespace uking::ai
