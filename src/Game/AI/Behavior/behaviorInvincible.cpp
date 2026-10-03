#include "Game/AI/Behavior/behaviorInvincible.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::behavior {

Invincible::Invincible(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

Invincible::~Invincible() = default;

bool Invincible::m6(sead::Heap* heap) {
    return true;
}

void Invincible::m7() {}

void Invincible::m8() {
    if (auto* mgr = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr()))
        mgr->mField_34 = true;
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unk = actor->m159())
            unk->sub_71006DFA04(true);
    }
}

void Invincible::m9() {
    if (auto* mgr = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr()))
        mgr->mField_34 = false;
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unk = actor->m159())
            unk->sub_71006DFA04(false);
    }
}

void Invincible::loadParams() {

}

}  // namespace uking::behavior
