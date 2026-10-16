#include "Game/Actor/Behavior/behaviorInvincible.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"

namespace uking::behavior {

Invincible::Invincible(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

Invincible::~Invincible() = default;

bool Invincible::init_(sead::Heap* heap) {
    return true;
}

void Invincible::calc() {}

void Invincible::enter() {
    if (auto* mgr = sead::DynamicCast<uking::act::DamageManager>(mActor->getDamageMgr()))
        mgr->mField_34 = true;
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unk = actor->m159())
            unk->sub_71006DFA04(true);
    }
}

void Invincible::leave() {
    if (auto* mgr = sead::DynamicCast<uking::act::DamageManager>(mActor->getDamageMgr()))
        mgr->mField_34 = false;
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unk = actor->m159())
            unk->sub_71006DFA04(false);
    }
}

void Invincible::loadParams() {

}

}  // namespace uking::behavior
